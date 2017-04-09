hzk-osd:main.o font.o mask.o bmp.o
	gcc -std=c99 -o $@ $^
%o:%c
	gcc -std=c99 -c $<
    
clean:
	rm -f *.o hzk-osd String.bmp Time.bmp