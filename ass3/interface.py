import sys
import numpy as np
import os
from statistics import mode
from pathlib import Path
import time
import rospy
from mover.msg import Direction

counter = 0
rospy.init_node('direction_talker', anonymous=True)
pub = rospy.Publisher('direction_cmd', Direction, queue_size=10)
# rate = rospy.Rate(1/30)

class createMap: # from ROS result to PAT input
    def __init__(self, name):
        self.name = name
        self.degree = self.getDegree()
        self.grid = self.storeInArray(name)
        self.range = self.rangeList()
        self.new_grid = self.reshapeGrid()
    
    def getDegree(self):
        lines = []
        with open('Map.txt','r') as fp:
            lines = fp.readlines()
        
        degree = []
        with open("Map.txt","w") as fp:
            for count, line in enumerate(lines):
                if count != 384:
                    fp.write(line)
                else:
                    degree = [int(i) for i in line.split() if i.isdigit()]      
        return degree
    
    def storeInArray(self, filename): # store txt file values in nd.array
        file = self.name
        count = 0
        grid = []
        original_grid = []

        with open(file) as f:           
            for line in f:
                real_grid = list(line.strip())
                filterd_arr = []

                for element in real_grid:               
                    if element != ' ':
                        filterd_arr.append(element)
				
                if '1' and '2' in filterd_arr:
                    grid.append(filterd_arr)
                
                filterd_arr = filterd_arr[2:382]
                original_grid.append(filterd_arr)
                count += 1
			
		
        original_grid = np.array(original_grid)
		
        grid = np.array(grid)
		
        for i in range(2):
            original_grid = np.delete(original_grid, 0, 0)
            original_grid = np.delete(original_grid, -1, 0)
    	
        return original_grid
	
    def printMap(self):
        return self.grid

    def rangeList(self):
        range_list = []
        for x in range(0, self.grid.shape[0]+1, 20):
            range_list.append(x)
        #print('range list = ', range_list)
        return range_list

    def reshapeGrid(self):
        new_array = []
        small_grid = []
        row = []

        count1 = 0
        for index, val in enumerate(self.range):
            small_grid = []
            count1 += 1
    
            if index+1 < 20:
                next_value = self.range[index+1]
                count2 = 0
        
                for num in range(1, 20):
                    row = []
                    count2 += 1
                    value = self.range[num] #20, 40, 60, 
            
                    for x in range(val, next_value): # 0 - 20, 20 -40
                        row.extend(self.grid[x][value-20 : value])
            
                    if '3' in row:
                        if count1 == 19 and count2 == 19:
                            small_grid.append('3];')
                        else:
                            small_grid.append('3,')
                    
                    elif '2' in row:
                        if count1 == 19 and count2 == 19:
                            small_grid.append('2];')
                        else:
                            small_grid.append('2,')
                    elif '1' in row:
                        if count1 == 19 and count2 == 19:
                            small_grid.append('1];')
                        else:
                            small_grid.append('1,')
                    else:
                        if count1 == 19 and count2 == 19:
                            small_grid.append('0];')
                        else:
                            small_grid.append('0,')
                            
                new_array.append(small_grid)
        new_array = np.array(new_array)
        #print('New shape is {}'.format(new_array.shape))
        return new_array

    def createCSPfile(self):
        # save new 19x19 grid to a new txt file
        np.savetxt("saveMap.txt", self.new_grid, fmt='%s')

        # write in a new txt file
        with open('ros.txt', 'w') as file:
            file.write('#define M {};\n'.format(self.new_grid.shape[0]))
            file.write('#define N {};\n'.format(self.new_grid.shape[1]))
            file.write('var D = {};\n'.format(self.degree[0]))
            with open('saveMap.txt') as f:
                file.write('var ROS[N][M] = \n[')
                for line in f.readlines():
                    file.write(line)

        # create Map.csp file
        my_file = 'ros.txt'
        base = os.path.splitext(my_file)[0]
        os.rename('ros.txt','Map.csp')
        
class getDirection: # from PAT result to ROS input
    def __init__(self, name):
        self.name = name
        
    def findDirection(self):
        output = []
        with open(self.name) as f:
            for line in f:
                if '<init ' in line:
                    output.append(line.split("->"))
                    
        count = 0   
        direction_msg = Direction()
        direction_msg.directions = []

        print(output[0])

        for value in output[0]:
            if count < 4:
                if 'left' in value:
                    direction_msg.directions.append('Left')
                    count += 1
                elif 'right' in value:
                    direction_msg.directions.append('Right')
                    count += 1
                elif 'fwd' in value:
                    direction_msg.directions.append('Forward')
                    count += 1
                else:
                    continue
            else:
                break


        direction_msg.counter = counter
        rospy.loginfo("Direction: %s, Counter: %s", direction_msg.directions, str(direction_msg.counter))
        pub.publish(direction_msg)
                
# check current directory
print("Current working directory: {0}".format(os.getcwd()))
directory = os.getcwd()
count = 0

while(1):

    # check if Map.txt file exists
    if count == 0:
        while(os.path.exists('Map.txt') == 0):
            print("\nWaiting for 'Map.txt' file...")
            time.sleep(10)
        print('\nMap.txt file acquired!')
        count += 1
    else:
        while(os.path.exists('commands_status.txt') == 0):
            print("\nWaiting for commands_status.txt file...")
            time.sleep(10)
        print('\ncommands_status.txt file acquired!')
        
        while(1):
            lines = []
            print('\nWaiting for ROS update...')
            with open('commands_status.txt') as f:
                for line in f:
                    lines.append(line)

                if 'true\n' == lines[1]:
                    time.sleep(40)
                    print('\nCongratulations! Robot arrived at the goal state!')
                    sys.exit()

                if 'true\n' == lines[0]:
                    print('\nMap.txt file acquired!')
                    break
        
            time.sleep(5)
        print('ROS updated!')
    
    # create csp map
    time.sleep(5)
    create_map = createMap('Map.txt')
    create_map.getDegree()
    create_map.printMap()
    create_map.createCSPfile()
    os.remove('saveMap.txt')
    os.remove('Map.txt')
    print("\n2D map created as 'Map.csp'!")
    
    # call pat
    os.chdir('/home/student/Desktop/MONO-PAT-v3.6.0')
    print("\nCurrent working directory changed: {0}".format(os.getcwd()))
    cmd = 'mono PAT3.Console.exe -csp -engine 1 ~/ass3/Ass.csp ~/ass3/Output.txt'
    os.system(cmd)
    print("\nPAT output created as 'Output.txt'")
    
    # create ros msg
    os.chdir(directory)
    print("\nCurrent working directory changed: {0}".format(os.getcwd()))
    direction = getDirection('Output.txt')
    direction.findDirection()
    counter += 1
    print("\nROS command created as 'ros.msg'!")