import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;

public class WebSocketConnection {
    Socket webSocket;
    DataInputStream inputStream;

    public WebSocketConnection(handleClient client) {
        webSocket = client.s;
        inputStream = new DataInputStream(client.input);
    }

    public void decodeData() throws IOException {
        byte[] resolverBytes = inputStream.readNBytes(10);
        int opcode = resolverBytes[0] & 0x0F;
        boolean isMasked = (resolverBytes[1] & 0x80) != 0;
        int lenGuess = resolverBytes[1] & 0x7F;
        if ( lenGuess > 125 ) {
            if ( lenGuess == 126 ) {
                byte[] guessLengthBytes = inputStream.readNBytes(2);
                lenGuess = inputStream.readUnsignedShort();
            } else if ( lenGuess == 127) {
                byte[] guessLengthBytes = inputStream.readNBytes(8);
                lenGuess = (int) inputStream.readLong();
            }
        }

        byte[] MASK = inputStream.readNBytes(4);
        byte[] ENCODED = inputStream.readNBytes(lenGuess);
        //byte[] DECODED = new byte[lenGuess];

        String DECODED = "";
        for (var i = 0; i < ENCODED.length; i++) {
            DECODED[i] = ENCODED[i] ^ MASK[i % 4];
        }

        System.out.println("OPCODE: " + opcode + " | Is Masked? " + isMasked + " | Guess Length? " + lenGuess );
        System.out.println("DECODED: ");
        System.out.println( decoded_message );


    }
}
