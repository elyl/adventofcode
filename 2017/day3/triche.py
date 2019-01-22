import math

input = 347991

def side_length(number):
        side = math.ceil(math.sqrt(number))
        side = side if side % 2 != 0 else side + 1
        return side

side = side_length(input)
steps_to_reach_center_from_axis = (side-1)/2
axises = [side**2 - ((side-1) * i)  - math.floor(side/2) for i in range(0, 4)] #get the axis "cells"
steps_to_reach_axix_from_input = min([abs(axis - input) for axis in axises])

print(steps_to_reach_axix_from_input + steps_to_reach_center_from_axis)
