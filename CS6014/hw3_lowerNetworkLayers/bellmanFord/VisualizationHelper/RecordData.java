package msd.benjones.VisualizationHelper;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class RecordData {

    private FileWriter fileWriter;
    private File file;

    public RecordData(String fileName) throws IOException {
        file = new File(fileName);
        file.createNewFile();
        fileWriter = new FileWriter(file, true);
        //fileWriter.write("Test,Size,Time Taken");
    }

    public void writeData(int size, double time) throws IOException {
        fileWriter.write(size + "," + time + "\n");
    }

    public void closeFile() throws IOException {
        fileWriter.close();
    }

}
