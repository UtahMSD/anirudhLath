import javafx.application.Application;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
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
     * Applications may create other stages, if needed, but they will not be primary stages.
     * @throws Exception if something goes wrong
     */

// Member Variables
     Player player = new Player();
    int sineWaveFrequency_;
    int sineWaveCount_ = 0;
    ArrayList<Integer> sineWaveIndices = new ArrayList<>();
    int squareWaveFrequency_;
    int squareWaveCount_ = 0;
    ArrayList<Integer> squareWaveIndices = new ArrayList<>();
    int whiteNoiseCount_ = 0;
    ArrayList<Integer> whiteNoiseIndices = new ArrayList<>();

// LineUnavailableException
    public SynthGUI() throws LineUnavailableException {
    }

// Main GUI loop
   @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Synthesizer");
        GridPane root = new GridPane();
        root.setHgap(10);
        root.setVgap(10);
        root.setAlignment(Pos.CENTER);

////////////////// SINE WAVE ///////////////////////////////////////////////////////////////////////////////////////////
        /// ROW 0
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
        root.add(sineWaveCounter, 2, 4, 1, 1);

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
        createSineWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
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
        deleteSineWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(deleteSineWave, 1, 4, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////// SQUARE WAVE /////////////////////////////////////////////////////////////////////////////////////////
        /// ROW 1
        // Square wave label
        Label squareWaveLabel = new Label();
        squareWaveLabel.setText("Square Wave Generator: ");
        root.add(squareWaveLabel, 0, 1, 1, 1);

        // Frequency Text Field
        TextField squareWaveFrequencyField = new TextField();
        squareWaveFrequencyField.setPromptText("Enter a frequency... integers only!");
        root.add(squareWaveFrequencyField, 1, 1, 1, 1);

        // Square wave label
        Label squareWaveCounter = new Label();
        squareWaveCounter.setText("Square Wave Count: " + squareWaveCount_);
        root.add(squareWaveCounter, 2, 5, 1, 1);

        // Create Square Wave Button
        Button createSquareWave = new Button();
        createSquareWave.setText("Create Square Wave");
        createSquareWave.setOnAction(event -> {
            squareWaveFrequency_ = Integer.parseInt(squareWaveFrequencyField.getText());
            Player.sounds.add(new SquareWave(squareWaveFrequency_));
            Player.update();
            squareWaveCount_++;
            squareWaveIndices.add(Player.sounds.size());
            squareWaveCounter.setText("Square Wave Count: " + squareWaveCount_);
        });
        createSquareWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(createSquareWave, 2, 1, 1, 1);

        // Delete Square Wave Button
        Button deleteSquareWave = new Button();
        deleteSquareWave.setText("Delete Previous Square Wave");
        deleteSquareWave.setOnAction(event -> {
            for (int i = Player.sounds.size() - 1; i >= 0; i--) {
                if (Player.sounds.get(i) instanceof SquareWave) {
                    Player.sounds.remove(i);
                    System.out.println("Deleted at index " + i);
                    squareWaveCount_--;
                    break;
                }
            }

            squareWaveCounter.setText("Square Wave Count: " + squareWaveCount_);
        });
        deleteSquareWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(deleteSquareWave, 1, 5, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////// WHITE NOISE /////////////////////////////////////////////////////////////////////////////////////////
        /// ROW 2
        // White wave label
        Label whiteNoiseLabel = new Label();
        whiteNoiseLabel.setText("White Noise Generator: ");
        root.add(whiteNoiseLabel, 0, 2, 1, 1);

        // Frequency Text Field
        TextField whiteNoiseFrequencyField = new TextField();
        whiteNoiseFrequencyField.setPromptText("Enter a frequency... integers only!");
        whiteNoiseFrequencyField.setVisible(false);
        root.add(whiteNoiseFrequencyField, 1, 2, 1, 1);

        // White wave label
        Label whiteNoiseCounter = new Label();
        whiteNoiseCounter.setText("White Noise Count: " + whiteNoiseCount_);
        root.add(whiteNoiseCounter, 2, 6, 1, 1);

        // Create White Noise Button
        Button createWhiteNoise = new Button();
        createWhiteNoise.setText("Create White Noise");
        createWhiteNoise.setOnAction(event -> {
            Player.sounds.add(new WhiteNoise());
            Player.update();
            whiteNoiseCount_++;
            whiteNoiseIndices.add(Player.sounds.size());
            whiteNoiseCounter.setText("White Noise Count: " + whiteNoiseCount_);
        });
        createWhiteNoise.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(createWhiteNoise, 2, 2, 1, 1);

        // Delete White Noise Button
        Button deleteWhiteNoise = new Button();
        deleteWhiteNoise.setText("Delete Previous White Noise");
        deleteWhiteNoise.setOnAction(event -> {
            for (int i = Player.sounds.size() - 1; i >= 0; i--) {
                if (Player.sounds.get(i) instanceof WhiteNoise) {
                    Player.sounds.remove(i);
                    System.out.println("Deleted at index " + i);
                    whiteNoiseCount_--;
                    break;
                }
            }

            whiteNoiseCounter.setText("White Noise Count: " + whiteNoiseCount_);
        });
        deleteWhiteNoise.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        root.add(deleteWhiteNoise, 1, 6, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////// Player Controls /////////////////////////////////////////////////////////////////////////////////////
        /// ROW 3
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
        root.add(play, 1, 3, 1, 1);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        primaryStage.setScene(new Scene(root, 500, 300));
        primaryStage.show();
    }
}
