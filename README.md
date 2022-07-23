# sm3_lengenthAttack
首先给出一个M1计算它对应的H1，随机选取M2，计算它对应的H2（IV更新为H1），计算M3（M1padding||M2)对应的H3，攻击成功：H2=H3
