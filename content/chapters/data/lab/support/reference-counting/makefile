DMD=dmd
DFLAGS=

operators: operators.d
	$(DMD) $(DFLAGS) $?

refcount_skel: refcount_skel.d
	$(DMD) $(DFLAGS) $?

clean:
	rm -rf *.o operators refcount_skel
