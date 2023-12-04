all: client serverSingle serverMulti

client: client.cpp
	g++ -std=c++17 client.cpp -o client 

serverSingle: serverSingle.cpp
	g++ -std=c++17 serverSingle.cpp -o serverSingle

serverMulti: serverMulti.cpp
	g++ -std=c++17 serverMulti.cpp -o serverMulti

clean:
	rm client
	rm serverSingle
	rm serverMulti