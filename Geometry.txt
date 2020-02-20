FYI:
    acos(x), asin(x) etc. functions always return radian value.
    For cos(theta), sin(theta) etc. functions theta has to be in radians.
    2 radians = 360 degrees
    Degree to radian:
        1 degree = (1 / 180) radians
        x degrees = x * (1 / 180) radians
    Radian to Degree:
        1 radian = 180 degrees
        x radians = x * 180 degrees

Constants:
    PI = acos(-1) 

Projectile:
    For a projectile launched at an angle,
        H = (u * u * sin(angle) * sin(angle)) / (2 * g)
        R = (u * u * sin(2 * angle)) / g
        T = (2 * u * sin(angle)) / g
    where H = maximum height, R = travelled distance, T = time of flight,
    g = free fall acceleration, angle = launch angle in radians
    It takes T / 2 time to reach the max height and T / 2 time to reach zero height
    from the maximum height.

Area:
    Area covered by three points (ax, ay), (bx, by) & (cx, cy):
        Area = abs((ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) / 2)