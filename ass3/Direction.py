import rospy
from mover.msg import Direction
import time

def talker():
    pub = rospy.Publisher('direction_cmd', Direction, queue_size=10)
    rospy.init_node('direction_talker', anonymous=True)
    rate = rospy.Rate(1/30) # approximately once every 30 seconds
    counter = 0
    time.sleep(5)

    while not rospy.is_shutdown():
        direction_msg = Direction()
        direction_msg.directions = ["Forward", "Left", "Forward", "Right", "Forward"]  # First array of directions
        direction_msg.counter = counter
        rospy.loginfo("Directions: %s, Counter: %s", direction_msg.directions, str(direction_msg.counter))
        pub.publish(direction_msg)
        counter += 1
        time.sleep(90)

        direction_msg.directions = ["Forward", "Left"]  # Second array of directions
        direction_msg.counter = counter
        rospy.loginfo("Directions: %s, Counter: %s", direction_msg.directions, str(direction_msg.counter))
        pub.publish(direction_msg) # Don't forget to publish the second set of directions
        counter += 1
        time.sleep(90)

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
