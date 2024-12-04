- test case 的档案名称和 test case 名称一致

- test case 命名：
    - 档案名使用：[Target hardware]\_[Test Item]_[1-9]（target hardware 采用缩写）
    
    - 其中[1-9]为可选内容：若[Target hardware]_[Test Item]一致则加入[1-9]以示区分
    
    - 档案名中统一使用大写
    
    - 并将其放在 test_case 的 Target Hardware 目录格式如下：
    
      ```cmd
      └── test_case
      ├── [Target Hardware]
      │   ├── [Target hardware]_[Test Item]_[1-9].yaml <--- test case 档案名（target hardware 采用缩写）
      ```


- 具体示例如下：

  ```cmd
  test_case
    ├── Ethernet_1
    │   ├── ETH_1_100M.yaml
    │   ├── ETH_1_10_100M.yaml
    │   └── ETH_1_10M.yaml
    ├── Ethernet_2
    │   ├── ETH_2_100M.yaml
    │   ├── ETH_2_10_100M.yaml
    │   └── ETH_2_10M.yaml
    └── JUSB20
        ├── USB_OTG_1_HOST.yaml
        ├── USB_OTG_1_USB2.0.yaml
        ├── USB_OTG_2_DEVICE.yaml
        └── USB_OTG_2_USB2.0.yaml
  ```
  
- 注：
    - Target hardware 与 Test Item 名称参考 [C8015] MS-C8015-0B-Release-Test-Plan.xlsx
    - target hardware 缩写
        - 优先采用 Target hardware 官方缩写
        - 其次使用该项目已使用为大家熟知的缩写
        - 不要自行缩写（若用则保证见名知意，同事进行注释）