$$\begin{aligned}&\ \ \ \ \ \sum_{j=1}^{n-1}\sum_a\sum_b(j-a)(j+b)
\\&=\sum_j\sum_a\sum_bj^2-aj+bj-ab
\\&=\sum_j\left(j^2c_ac_b-c_bs_aj+c_as_bj-s_as_b\right)\end{aligned}$$

（$c_a$ 表示共有 $c_a$ 个 $a$，$s_a$ 表示 $\sum a$）  
然后用 PAM 维护 $c_a,s_a$ 就行了。