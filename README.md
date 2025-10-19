loipon



![image info](./images/blue_red_gradient.png)

```
fill(pixels, WIDTH, HEIGHT, 0xebac4e);
Point p = {WIDTH / 2, HEIGHT / 2};
circle(pixels, WIDTH, HEIGHT, p, 164, 0x111806);
draw_checker(pixels, WIDTH, HEIGHT, 8, 8, 0xfb01d2);
circle(pixels, WIDTH, HEIGHT, p, 102, 0x39b31b);
draw_checker(pixels, WIDTH, HEIGHT, 8, 8, 0xfb01d2);

p.x = WIDTH/4;
p.y = HEIGHT/4;
circle(pixels, WIDTH, HEIGHT, p, 32, 0xdddddd);
p.x = WIDTH/4 + WIDTH/2;
circle(pixels, WIDTH, HEIGHT, p, 32, 0xdddddd);
p.y = WIDTH/4 + WIDTH/2;
circle(pixels, WIDTH, HEIGHT, p, 32, 0xdddddd);
p.x = WIDTH/4;
circle(pixels, WIDTH, HEIGHT, p, 32, 0xdddddd);
```

![image info](./images/random.png)
