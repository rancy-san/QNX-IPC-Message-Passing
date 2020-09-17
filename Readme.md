## IPC Message Passing

### Description
This real time program creates a client that sends a message containing two integers and a character representing the operation to a server. The server computes the numeric value for the result of the numbers and the given operation, and then returns a message containing a structure as the result. The client will pass the two numbers as integer members of an “input parameters” struct and the operation as a character value in the struct. The server will reply with a different struct containing a double, a flag representing whether or not an error occurred (or would have occurred if the operation had been attempted), and a character string of up to 128 bytes containing the error description. (You can use your imagination for the string content but try to cover all types of errors.)
The operation should be one of: ‘+’, ‘-‘, ‘x’, and ‘/’. (Note: that is an ‘x’ not a ‘*’). The input integer values could be any valid integer. The server must check for division by 0. The client should check for valid inputs.
Start the server in the background (use the ‘&’ symbol) and print its process_id (PID). Then multiple client applications could be run in the foreground that use a command-line argument on the client application to pass the PID of the server which they want to use to perform the operation.
The client program will block until receiving the result message from the server program and then the client program will output the result (or error condition) to the console. You can find an example below.

### Example
#./calc_server &
The server is running as PID 77234

#./calc_client 77234 6 + 9
The server has calculated the result of 6 + 9 as 15.