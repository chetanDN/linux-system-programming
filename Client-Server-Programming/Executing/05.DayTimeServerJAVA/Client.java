import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client {

	public final static int DEFAULT_PORT = 13;

	public static void main(String[] args) {

		int port = DEFAULT_PORT;

		try {

			Socket clientSocket = new Socket("localhost",port);
			BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			String reply = inFromServer.readLine();
			System.out.println("from Server: "+reply);
			
			clientSocket.close();			

		} // end try
		catch (IOException ex) {
			System.err.println(ex);
		} // end catch

	} // end main

} // end DaytimeServer
