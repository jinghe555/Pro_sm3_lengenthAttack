# 项目名称 
sm3_lengenthAttack
# 项目简介
 长度扩展攻击（length extension attack），是指针对某些允许包含额外信息的加密散列函数的攻击手段。对于满足以下条件的散列函数，都可以作为攻击对象：

       ① 加密前将待加密的明文按一定规则填充到固定长度（例如512或1024比特）的倍数；

       ② 按照该固定长度，将明文分块加密，并用前一个块的加密结果，作为下一块加密的初始向量（Initial Vector）。
# 完成人
何静
# 项目流程
首先给出一个M1计算它对应的H1，随机选取M2，计算它对应的H2（IV更新为H1）
计算M3（M1padding||M2)对应的H3，攻击成功：H2=H3
# 部分代码说明
在之前实现的sm3算法上进行攻击
![image](https://user-images.githubusercontent.com/104714591/181266608-f9a34248-4c5c-4829-8ca7-2572d03e813c.png)
![image](https://user-images.githubusercontent.com/104714591/181266677-0e2974e1-b28a-41e3-8c36-d183694d479f.png)

# 运行过程截图
![image](https://user-images.githubusercontent.com/104714591/181264097-950e81fb-6bac-4b8a-a05e-836651c5f582.png)
# 引用参考
https://blog.csdn.net/szuaurora/article/details/78125585
