;; Auto-generated. Do not edit!


(when (boundp 'mover::Direction)
  (if (not (find-package "MOVER"))
    (make-package "MOVER"))
  (shadow 'Direction (find-package "MOVER")))
(unless (find-package "MOVER::DIRECTION")
  (make-package "MOVER::DIRECTION"))

(in-package "ROS")
;;//! \htmlinclude Direction.msg.html


(defclass mover::Direction
  :super ros::object
  :slots (_directions _counter ))

(defmethod mover::Direction
  (:init
   (&key
    ((:directions __directions) (let (r) (dotimes (i 0) (push "" r)) r))
    ((:counter __counter) 0)
    )
   (send-super :init)
   (setq _directions __directions)
   (setq _counter (round __counter))
   self)
  (:directions
   (&optional __directions)
   (if __directions (setq _directions __directions)) _directions)
  (:counter
   (&optional __counter)
   (if __counter (setq _counter __counter)) _counter)
  (:serialization-length
   ()
   (+
    ;; string[] _directions
    (apply #'+ (mapcar #'(lambda (x) (+ 4 (length x))) _directions)) 4
    ;; int32 _counter
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string[] _directions
     (write-long (length _directions) s)
     (dolist (elem _directions)
       (write-long (length elem) s) (princ elem s)
       )
     ;; int32 _counter
       (write-long _counter s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string[] _directions
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _directions (make-list n))
     (dotimes (i n)
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setf (elt _directions i) (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
     ))
   ;; int32 _counter
     (setq _counter (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mover::Direction :md5sum-) "64e541ae8bb2db4768685ff2c7898ac4")
(setf (get mover::Direction :datatype-) "mover/Direction")
(setf (get mover::Direction :definition-)
      "string[] directions
int32 counter
")



(provide :mover/Direction "64e541ae8bb2db4768685ff2c7898ac4")


