# HZK-OSD
## 功能
根据指定字符串信息，从hzk16字体库中读取相应字符的点阵数据，然后写入RGB555格式的BMP图像中，可用于在视频中以BMP图像形式叠加字符OSD信息。
本程序支持GB2312编码格式的汉字和英文字母等半角符号。
## 示例
字符信息   
![字符串信息BMP](Sample-String.bmp "Title")   
时间戳信息   
![时间戳信息BMP](Sample-Time.bmp "Title")   
## 说明
**font** 目录下为hzk16字体文件。
RGB555格式BMP图像格式为：

```
+------------------+------------------+----------------+
| BitmapFileHeader | BitmapInfoHeader |  BMP Data ...  |
+------------------+------------------+----------------+
```
常见的BMP图像其BMP Data数据为倒序的，即数据从最后一行开始，第一行的数据在文件最后。