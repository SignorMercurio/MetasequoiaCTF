# jwt

JSON Web Token算法篡改攻击，看了[这篇文章](https://www.anquanke.com/post/id/145540#h3-8)后改的题。最后访问`admin`的`note`的时候，会得到一个url路径，访问该路径即为flag。这样做是为了支持动态flag，因为sqlite对读文件的支持不是特别好。