# Babysmali

题目给了`smali.jar`以及`src.smali`，我们先将后者汇编成`dex`文件。
```bash
java -jar smali.jar assemble src.smali -o src.dex
```

然后使用jadx反编译`dex`文件：
```java
package com.example.hellosmali.hellosmali;

public class Digest {
    public static boolean check(String input) {
        String str = "+/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        if (input == null || input.length() == 0) {
            return false;
        }
        int i;
        char[] charinput = input.toCharArray();
        StringBuilder v2 = new StringBuilder();
        for (char toBinaryString : charinput) {
            String intinput = Integer.toBinaryString(toBinaryString);
            while (intinput.length() < 8) {
                intinput = "0" + intinput;
            }
            v2.append(intinput);
        }
        while (v2.length() % 6 != 0) {
            v2.append("0");
        }
        String v1 = String.valueOf(v2);
        char[] v4 = new char[(v1.length() / 6)];
        for (i = 0; i < v4.length; i++) {
            int v6 = Integer.parseInt(v1.substring(0, 6), 2);
            v1 = v1.substring(6);
            v4[i] = str.charAt(v6);
        }
        StringBuilder v3 = new StringBuilder(String.valueOf(v4));
        if (input.length() % 3 == 1) {
            v3.append("!?");
        } else if (input.length() % 3 == 2) {
            v3.append("!");
        }
        if (String.valueOf(v3).equals("xsZDluYYreJDyrpDpucZCo!?")) {
            return true;
        }
        return false;
    }
}
```

从字符集可以看出和Base64编码有关，实际上只是它的一个变种。既可以用python解，也可以用java解，python版：
```py
import string

base64_charset = '+/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789'

def decode(base64_str):
    """
    解码base64字符串
    :param base64_str:base64字符串
    :return:解码后的bytearray；若入参不是合法base64字符串，返回空bytearray
    """
    # 对每一个base64字符取下标索引，并转换为6为二进制字符串
    base64_bytes = ['{:0>6}'.format(str(bin(base64_charset.index(s))).replace('0b', '')) for s in base64_str if
                    s != '=']
    resp = bytearray()
    nums = len(base64_bytes) // 4
    remain = len(base64_bytes) % 4
    integral_part = base64_bytes[0:4 * nums]

    while integral_part:
        # 取4个6位base64字符，作为3个字节
        tmp_unit = ''.join(integral_part[0:4])
        tmp_unit = [int(tmp_unit[x: x + 8], 2) for x in [0, 8, 16]]
        for i in tmp_unit:
            resp.append(i)
        integral_part = integral_part[4:]

    if remain:
        remain_part = ''.join(base64_bytes[nums * 4:])
        tmp_unit = [int(remain_part[i * 8:(i + 1) * 8], 2) for i in range(remain - 1)]
        for i in tmp_unit:
            resp.append(i)

    return resp

if __name__=="__main__":
    print decode('A0NDlKJLv0hTA1lDAuZRgo==')
```

java版：
```java
public class XMan {
    public static void main(String[] args) {
        String v6 = "+/abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        String s = "xsZDluYYreJDyrpDpucZCo";
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < s.length(); i++) {
            int tmp = v6.indexOf(s.charAt(i));
            String ss = Integer.toBinaryString(tmp);
            if (ss.length() == 5) {
                ss = "0" + ss;
            } else if (ss.length() == 4) {
                ss = "00" + ss;
            } else if (ss.length() == 3) {
                ss = "000" + ss;
            } else if (ss.length() == 2) {
                ss = "0000" + ss;
            } else if (ss.length() == 1) {
                ss = "00000" + ss;
            } else if (ss.length() == 0) {
                ss = "000000" + ss;
            }
            sb.append(ss);
        }
        String x = sb.toString() + "0000";
        StringBuilder stringBuilder = new StringBuilder();
        for (int i = 0; i < x.length(); i += 8) {
            String tmp = x.substring(i, i + 8);
            byte b = (byte) Integer.parseInt(tmp, 2);
            stringBuilder.append((char) b);
        }
        System.out.println(stringBuilder.toString());


    }
}
```