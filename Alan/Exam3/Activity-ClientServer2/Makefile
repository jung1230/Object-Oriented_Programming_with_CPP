all: client serverSingle 

client: client.cpp
	g++ -std=c++17 client.cpp -o client 

serverSingle: serverSingle.cpp
	g++ -std=c++17 serverSingle.cpp -o serverSingle

clean:
	rm client
	rm serverSingle