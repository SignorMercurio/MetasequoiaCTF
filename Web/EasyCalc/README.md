# EasyCalc

计算器题很容易想到让除数为0试试，随后可以发现是Python Flask后端，尝试模板注入。先泄露`config`得到`secret_key`，然后用`solve.py`脚本伪造Flask Session读flag，注意绕过`os`的过滤。