
(cl:in-package :asdf)

(defsystem "mover-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "MovementComplete" :depends-on ("_package_MovementComplete"))
    (:file "_package_MovementComplete" :depends-on ("_package"))
  ))