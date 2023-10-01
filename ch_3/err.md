 *  Executing task: C/C++: g++ build active file 

Starting build...
/usr/bin/g++ -fdiagnostics-color=always -g /home/charl/code/data_structures/ch_3/**.cpp -o /home/charl/code/data_structures/ch_3/main
/home/charl/code/data_structures/ch_3/main.cpp: In function ‘Flight& getFlight(SLList<Flight>&, int)’:
/home/charl/code/data_structures/ch_3/main.cpp:47:42: warning: reference to local variable ‘flight’ returned [-Wreturn-local-addr]
   47 |         if (flight.getId() == id) return flight;
      |                                          ^~~~~~
/home/charl/code/data_structures/ch_3/main.cpp:46:16: note: declared here
   46 |         Flight flight = list.at(i);
      |                ^~~~~~
/home/charl/code/data_structures/ch_3/main.cpp:53:1: warning: control reaches end of non-void function [-Wreturn-type]
   53 | };
      | ^
/usr/bin/ld: /tmp/ccfPACXy.o: in function `Driver()':
/home/charl/code/data_structures/ch_3/main.cpp:18: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::SLList()'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:18: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::SLList()'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:27: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::orderInsert(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:28: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::orderInsert(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:32: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::out()'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:33: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::out()'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `getFlight(SLList<Flight>&, int)':
/home/charl/code/data_structures/ch_3/main.cpp:46: undefined reference to `SLList<Flight>::at(int)'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:45: undefined reference to `SLList<Flight>::length()'
/usr/bin/ld: /home/charl/code/data_structures/ch_3/main.cpp:51: undefined reference to `SLList<Flight>::pushBack(Flight)'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `main':
/home/charl/code/data_structures/ch_3/main.cpp:105: undefined reference to `SLList<Flight>::SLList()'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `Flight::Flight(int)':
/home/charl/code/data_structures/ch_3/Flight.h:10: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::SLList()'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `Flight::addPassenger(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)':
/home/charl/code/data_structures/ch_3/Flight.h:14: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::orderInsert(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `Flight::removePassenger(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)':
/home/charl/code/data_structures/ch_3/Flight.h:15: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::removeFirst(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >)'
/usr/bin/ld: /tmp/ccfPACXy.o: in function `Flight::printPassengers()':
/home/charl/code/data_structures/ch_3/Flight.h:16: undefined reference to `SLList<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > >::out()'
collect2: error: ld returned 1 exit status

Build finished with error(s).