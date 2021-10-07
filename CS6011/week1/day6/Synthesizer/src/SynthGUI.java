import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;

public class SynthGUI extends Application {
    /**
     * The main entry point for all JavaFX applications. The start method is called after the init method has returned,
     * and after the system is ready for the application to begin running.
     *
     * <p>
     * NOTE: This method is called on the JavaFX Application Thread.
     * </p>
     *
     * @param primaryStage the primary stage for this application, onto which the application scene can be set.
     *                     Applications may create other stages, if needed, but they will not be primary stages.
     * @throws Exception if something goes wrong
     */

    Player player = new Player();
    int sineWaveFrequency_;
    int sineWaveCount_ = 0;
    ArrayList<Integer> sineWaveIndices = new ArrayList<>();



    public SynthGUI() throws LineUnavailableException {
    }


    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Synthesizer");
        GridPane root = new GridPane();
        root.setHgap(10);
        root.setVgap(10);
        root.setAlignment(Pos.CENTER);
        //StackPane root = new StackPane();

        // Sine wave label
        Label sineWaveLabel = new Label();
        sineWaveLabel.setText("Sine Wave Generator: ");
        root.add(sineWaveLabel, 0, 0, 1, 1);

        // Frequency Text Field
        TextField frequencyField = new TextField();
        frequencyField.setPromptText("Enter a frequency... integers only!");
        root.add(frequencyField, 1, 0, 1, 1);

        // Sine wave label
        Label sineWaveCounter = new Label();
        sineWaveCounter.setText("Sine Wave Count: " + sineWaveCount_);
        root.add(sineWaveCounter, 2, 3, 1, 1);

        // Create Sine Wave Button
        Button createSineWave = new Button();
        createSineWave.setText("Create Sine Wave");
        createSineWave.setOnAction(event -> {
            sineWaveFrequency_ = Integer.parseInt(frequencyField.getText());
            Player.sounds.add(new SineWave(sineWaveFrequency_));
            Player.update();
            sineWaveCount_++;
            sineWaveIndices.add(Player.sounds.size());
            sineWaveCounter.setText("Sine Wave Count: " + sineWaveCount_);
        });
        root.add(createSineWave, 2, 0, 1, 1);

        // Delete Sine Wave Button
        Button deleteSineWave = new Button();
        deleteSineWave.setText("Delete Previous Sine Wave");
        deleteSineWave.setOnAction(event -> {
            for (int i = Player.sounds.size() - 1; i >= 0; i--) {
                if (Player.sounds.get(i) instanceof SineWave) {
                    Player.sounds.remove(i);
                    System.out.println("Deleted at index " + i);
                    sineWaveCount_--;
                    break;
                }
            }

            sineWaveCounter.setText("Sine Wave Count: " + sineWaveCount_);
        });
        root.add(deleteSineWave, 1, 3, 1, 1);




        // Play Button
        Button play = new Button();
        play.setText("Play");
        play.setOnAction(event -> {
            try {
                if (play.getText().equals("Play")) {
                    Player.play(0);
                    play.setText("Replay");
                } else {
                    Player.update();
                    Player.replay(0);
                }
            } catch (LineUnavailableException e) {
                e.printStackTrace();
            }

        });
        play.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(play, 1, 1, 1, 1);



        primaryStage.setScene(new Scene(root, 500, 250));
        primaryStage.show();
    }
}
