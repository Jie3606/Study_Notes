---
marp: true
theme: gaia
footer: 'jieliu 2024-09-20'
paginate: true
style: |
  section a {
      font-size: 25px;
  }
---

<!-- slide -->
Introduction to IIC Protocol
<!-- slide -->
Outline
___
- I2C Introduction
- I2C Physical layer
- I2C Protocol layer
- I2C application layer
- References
<!-- slide -->
I2C（Inter-Integrated Circuit）
---
- 一种非常常用的低速 （100 ~ 400 kHz） 总线，用于将板载和外部设备连接到处理器。
- 仅使用两条线： SDA 用于数据， SCL 用于 clock。
- 不可即插即用。
- 它是一个主/从总线：只有 master 可以发起通信，而 slave 只能回复 master 发起的通信。
- 每个从设备都由一个 I2C 地址标识（您不能在同一总线上有 2 个具有相同地址的设备）。主服务器发起的每笔通信都包含此地址，它允许相关的从服务器识别它应该回复此特定通信。
<!-- slide -->
Example of IIC-bus application
---
![alt text](image.png)
- 总线通过上拉电阻接到电源。当I2C设备空闲时，会输出高阻态，而当所有设备都空闲， 都输出高阻态时，由上拉电阻把总线拉成高电平。
- 多个主机同时使用总线时，为了防止数据冲突，会利用仲裁方式决定由哪个设备占用总线
<!-- slide -->
- start: DAT falling while CLK is high
- I2C Address is 7 bits
- Write: 0; read: 1
- ACK: 0; NACK: 1
- stop: DAT rising while CLK is high
![alt text](image-1.png)
<!-- slide -->
![alt text](image-2.png)
<!-- slide -->

<!-- slide -->
<!-- slide -->
<!-- slide -->
Thank you!
<!-- slide -->

