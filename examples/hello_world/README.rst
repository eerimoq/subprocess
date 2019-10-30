Build and run
=============

.. code-block:: text

   $ make
   gcc -I ../../include main.c ../../src/subprocess.c -o main
   ./main
   exit_code: 0
   stdout (length: 23):
   Hello World on stdout!

   stderr (length: 23):
   Hello World on stderr!
