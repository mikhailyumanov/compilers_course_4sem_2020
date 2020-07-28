# compilers_course_4sem_2020

See test 13 to know how irtree canonization visitors work.

There are 4 log files of subsequent visitors using:
* DoubleCallEliminationVisitor - in ...irtree_without_double_calls.txt

the visitor replaces *all* CALL(f, args) with ESEQ(MOVE(TEMP t, CALL(f, args)), t).
If any will not be replaced, it will disappear at the next stage.

* EseqEliminationVisitor - in ...irtree_without_eseq.txt

the visitor removes all ESEQ nodes from irtree from the previous stage.

* LinearizeVisitor - in ...irtree_without_eseq.txt

the visitor makes linear irtree.
