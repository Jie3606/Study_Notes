static const struct rtc_class_ops ds1672_rtc_ops = {
	.read_time = ds1672_read_time,
	.set_time = ds1672_set_time,
};

static int ds1672_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int err = 0;
	struct rtc_device *rtc;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		return -ENODEV;

	rtc = devm_rtc_allocate_device(&client->dev);
	if (IS_ERR(rtc))
		return PTR_ERR(rtc);

	rtc->ops = &ds1672_rtc_ops;
	rtc->range_max = U32_MAX;

	err = rtc_register_device(rtc);

	i2c_set_clientdata(client, rtc);

	return 0;
}

static const struct i2c_device_id ds1672_id[] = {
	{ "ds1672", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, ds1672_id);

static const struct of_device_id ds1672_of_match[] = {
	{ .compatible = "dallas,ds1672" },
	{ }
};
MODULE_DEVICE_TABLE(of, ds1672_of_match);

static struct i2c_driver ds1672_driver = {
	.driver = {
		   .name = "rtc-ds1672",
		   .of_match_table = of_match_ptr(ds1672_of_match),
	},
	.probe = &ds1672_probe,
	.id_table = ds1672_id,
};

module_i2c_driver(ds1672_driver);

MODULE_AUTHOR("Alessandro Zummo <a.zummo@towertech.it>");
MODULE_DESCRIPTION("Dallas/Maxim DS1672 timekeeper driver");
MODULE_LICENSE("GPL");