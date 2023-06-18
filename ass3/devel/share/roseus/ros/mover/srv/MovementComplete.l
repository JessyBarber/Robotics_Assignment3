;; Auto-generated. Do not edit!


(when (boundp 'mover::MovementComplete)
  (if (not (find-package "MOVER"))
    (make-package "MOVER"))
  (shadow 'MovementComplete (find-package "MOVER")))
(unless (find-package "MOVER::MOVEMENTCOMPLETE")
  (make-package "MOVER::MOVEMENTCOMPLETE"))
(unless (find-package "MOVER::MOVEMENTCOMPLETEREQUEST")
  (make-package "MOVER::MOVEMENTCOMPLETEREQUEST"))
(unless (find-package "MOVER::MOVEMENTCOMPLETERESPONSE")
  (make-package "MOVER::MOVEMENTCOMPLETERESPONSE"))

(in-package "ROS")





(defclass mover::MovementCompleteRequest
  :super ros::object
  :slots ())

(defmethod mover::MovementCompleteRequest
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass mover::MovementCompleteResponse
  :super ros::object
  :slots (_completed ))

(defmethod mover::MovementCompleteResponse
  (:init
   (&key
    ((:completed __completed) nil)
    )
   (send-super :init)
   (setq _completed __completed)
   self)
  (:completed
   (&optional (__completed :null))
   (if (not (eq __completed :null)) (setq _completed __completed)) _completed)
  (:serialization-length
   ()
   (+
    ;; bool _completed
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _completed
       (if _completed (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _completed
     (setq _completed (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass mover::MovementComplete
  :super ros::object
  :slots ())

(setf (get mover::MovementComplete :md5sum-) "9e58faa17a4877a1efc0e251b503c53b")
(setf (get mover::MovementComplete :datatype-) "mover/MovementComplete")
(setf (get mover::MovementComplete :request) mover::MovementCompleteRequest)
(setf (get mover::MovementComplete :response) mover::MovementCompleteResponse)

(defmethod mover::MovementCompleteRequest
  (:response () (instance mover::MovementCompleteResponse :init)))

(setf (get mover::MovementCompleteRequest :md5sum-) "9e58faa17a4877a1efc0e251b503c53b")
(setf (get mover::MovementCompleteRequest :datatype-) "mover/MovementCompleteRequest")
(setf (get mover::MovementCompleteRequest :definition-)
      "---
bool completed
")

(setf (get mover::MovementCompleteResponse :md5sum-) "9e58faa17a4877a1efc0e251b503c53b")
(setf (get mover::MovementCompleteResponse :datatype-) "mover/MovementCompleteResponse")
(setf (get mover::MovementCompleteResponse :definition-)
      "---
bool completed
")



(provide :mover/MovementComplete "9e58faa17a4877a1efc0e251b503c53b")


