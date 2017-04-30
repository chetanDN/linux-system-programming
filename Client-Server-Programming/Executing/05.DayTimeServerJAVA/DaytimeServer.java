/*
Design, develop, and execute a program using JAVA networking facilities to implement a simple Day / Time Server and demonstrate its functioning. Repeat the above problems.
*/

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Date;

public class DaytimeServer {

	public final static int DEFAULT_PORT = 13;

	public static void main(String[] args) {

		int port = DEFAULT_PORT;

		try {

			ServerSocket server = new ServerSocket(port); // important
			Socket connectionSocket = null;
			while (true) {

				try {
					connectionSocket = server.accept();
					Writer out = new OutputStreamWriter(connectionSocket.getOutputStream());
					Date now = new Date();
					out.write(now.toString() + "\r\n");
					out.flush();
					connectionSocket.close();
				} catch (IOException ex) {
				} finally {
					try {
						if (connectionSocket != null)
							connectionSocket.close();
					} catch (IOException ex) {
					}
				}

			} // end while

		} // end try
		catch (IOException ex) {
			System.err.println(ex);
		} // end catch

	} // end main

} // end DaytimeServer
