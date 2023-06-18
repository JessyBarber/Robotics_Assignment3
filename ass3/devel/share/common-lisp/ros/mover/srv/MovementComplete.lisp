; Auto-generated. Do not edit!


(cl:in-package mover-srv)


;//! \htmlinclude MovementComplete-request.msg.html

(cl:defclass <MovementComplete-request> (roslisp-msg-protocol:ros-message)
  ()
)

(cl:defclass MovementComplete-request (<MovementComplete-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MovementComplete-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MovementComplete-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mover-srv:<MovementComplete-request> is deprecated: use mover-srv:MovementComplete-request instead.")))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MovementComplete-request>) ostream)
  "Serializes a message object of type '<MovementComplete-request>"
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MovementComplete-request>) istream)
  "Deserializes a message object of type '<MovementComplete-request>"
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MovementComplete-request>)))
  "Returns string type for a service object of type '<MovementComplete-request>"
  "mover/MovementCompleteRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MovementComplete-request)))
  "Returns string type for a service object of type 'MovementComplete-request"
  "mover/MovementCompleteRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MovementComplete-request>)))
  "Returns md5sum for a message object of type '<MovementComplete-request>"
  "9e58faa17a4877a1efc0e251b503c53b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MovementComplete-request)))
  "Returns md5sum for a message object of type 'MovementComplete-request"
  "9e58faa17a4877a1efc0e251b503c53b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MovementComplete-request>)))
  "Returns full string definition for message of type '<MovementComplete-request>"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MovementComplete-request)))
  "Returns full string definition for message of type 'MovementComplete-request"
  (cl:format cl:nil "~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MovementComplete-request>))
  (cl:+ 0
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MovementComplete-request>))
  "Converts a ROS message object to a list"
  (cl:list 'MovementComplete-request
))
;//! \htmlinclude MovementComplete-response.msg.html

(cl:defclass <MovementComplete-response> (roslisp-msg-protocol:ros-message)
  ((completed
    :reader completed
    :initarg :completed
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass MovementComplete-response (<MovementComplete-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MovementComplete-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MovementComplete-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mover-srv:<MovementComplete-response> is deprecated: use mover-srv:MovementComplete-response instead.")))

(cl:ensure-generic-function 'completed-val :lambda-list '(m))
(cl:defmethod completed-val ((m <MovementComplete-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mover-srv:completed-val is deprecated.  Use mover-srv:completed instead.")
  (completed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MovementComplete-response>) ostream)
  "Serializes a message object of type '<MovementComplete-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'completed) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MovementComplete-response>) istream)
  "Deserializes a message object of type '<MovementComplete-response>"
    (cl:setf (cl:slot-value msg 'completed) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MovementComplete-response>)))
  "Returns string type for a service object of type '<MovementComplete-response>"
  "mover/MovementCompleteResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MovementComplete-response)))
  "Returns string type for a service object of type 'MovementComplete-response"
  "mover/MovementCompleteResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MovementComplete-response>)))
  "Returns md5sum for a message object of type '<MovementComplete-response>"
  "9e58faa17a4877a1efc0e251b503c53b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MovementComplete-response)))
  "Returns md5sum for a message object of type 'MovementComplete-response"
  "9e58faa17a4877a1efc0e251b503c53b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MovementComplete-response>)))
  "Returns full string definition for message of type '<MovementComplete-response>"
  (cl:format cl:nil "bool completed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MovementComplete-response)))
  "Returns full string definition for message of type 'MovementComplete-response"
  (cl:format cl:nil "bool completed~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MovementComplete-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MovementComplete-response>))
  "Converts a ROS message object to a list"
  (cl:list 'MovementComplete-response
    (cl:cons ':completed (completed msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'MovementComplete)))
  'MovementComplete-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'MovementComplete)))
  'MovementComplete-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MovementComplete)))
  "Returns string type for a service object of type '<MovementComplete>"
  "mover/MovementComplete")