# PasswordManager(pswdM) 0.0.3
# 自制本地密码管理器 0.0.3

1 The expected functions have not been fully implemented. The current version is only the basic function version. In the future, functions will be improved, security will be strengthened, and other optimizations will be made.

1 该管理器的预期功能还并没有完全实现，目前版本仅是基础功能版，后续将进行功能完善，加强安全性，并进行其他优化。

2 Although it can be used normally now, there are still some unresolved vulnerabilities. The solutions for these vulnerabilities have been formed, but due to time constraints and other reasons, no code updates have been made for the time being.

2 尽管现在已经可以正常使用，但仍然遗留了一些未解决的漏洞。这些漏洞的解决方案已经成型，但是由于时间紧迫等原因，暂时没有进行代码更新。

3 Note that the current version password storage file is not secure. Please do not use it for purposes with security requirements.

3 注意，目前版本密码储存文件并不安全，请不要用于有安全性要求的用途。

## Warning, Bug detected! 注意，发现重大BUG！

该版本程序在使用过程中被发现有重大漏洞，表现为读取部分明文文本时会无视换行符，最后复制到剪切板的为两行拼接结果。为了您和您的密码的安全，请暂停使用该版本，新的版本正在使用Base64重构中。

This version of the program was found to have major vulnerabilities during use, which was manifested by ignoring line breaks when reading part of plaintext text, and finally copying the result of two-line stitching to the clipboard. For the security of you and your password, please suspend this version, the new version is being refactored with Base64.


