// Import Libraries
import javafx.application.Application;
import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.*;
import javafx.scene.shape.Circle;
import javafx.stage.Stage;
import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;

public class SynthGUI extends Application {

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

    BorderPane grandParent = new BorderPane();
    AnchorPane parent = new AnchorPane();
    VBox leftSide = new VBox();
    VBox rightSide = new VBox();
    HBox topSide = new HBox();
    HBox bottomSide = new HBox();
    static Circle speaker_;

    // LineUnavailableException
    public SynthGUI() throws LineUnavailableException {
    }

    // Main GUI loop
    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Synthesizer");



        // Top Side - Media Controls
        topSide.setStyle("-fx-background-color: lightblue;");
        Button play = new Button("Play");
        play.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        topSide.setAlignment(Pos.CENTER);
        topSide.setPadding(new Insets(5,5,5,5));
        topSide.setSpacing(10);
        topSide.getChildren().add(play);
        grandParent.setTop(topSide);

        // Left Side - Filters
        leftSide.setStyle("-fx-background-color: lightblue");
        Label createFilter = new Label("Create Filters");
        leftSide.setAlignment(Pos.TOP_CENTER);
        Button createVolumeFilter = new Button("Create Volume");
        createVolumeFilter.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        leftSide.setPadding(new Insets(5,5,5,5));
        leftSide.setSpacing(10);
        leftSide.getChildren().add(createFilter);
        leftSide.getChildren().add(createVolumeFilter);
        grandParent.setLeft(leftSide);

        // Center Side - Canvas
        parent.setStyle("-fx-background-color: lightgreen;");
        Bounds bound = parent.getBoundsInLocal();
        speaker_ = new Circle(20);
        AnchorPane.setTopAnchor(speaker_, 20.0);
        AnchorPane.setRightAnchor(speaker_, 20.0);

        parent.getChildren().add(speaker_);
        parent.setPadding(new Insets(5,5,5,5));
        grandParent.setCenter(parent);


        // Right Side - Sounds
        rightSide.setStyle("-fx-background-color: lightblue;");
        Label createSound = new Label("Create Sounds");
        rightSide.setAlignment(Pos.TOP_CENTER);
        Button createSineWave = new Button("Create Sine Wave");
        createSineWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        Button createSquareWave = new Button("Create Square Wave");
        createSquareWave.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        Button createWhiteNoise = new Button("Create White Noise");
        createWhiteNoise.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        rightSide.setPadding(new Insets(5,5,5,5));
        rightSide.setSpacing(10);
        rightSide.getChildren().add(createSound);
        rightSide.getChildren().add(createSineWave);
        rightSide.getChildren().add(createSquareWave);
        rightSide.getChildren().add(createWhiteNoise);
        grandParent.setRight(rightSide);

        // Bottom Side - Node Controls
        bottomSide.setStyle("-fx-background-color: lightblue;");
        Button deleteNode = new Button("Delete Node");
        deleteNode.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        bottomSide.setAlignment(Pos.CENTER);
        bottomSide.setPadding(new Insets(5,5,5,5));
        bottomSide.setSpacing(10);
        bottomSide.getChildren().add(deleteNode);
        grandParent.setBottom(bottomSide);

        // Buttons Event Handling
        createSineWave.setOnAction(e -> createSineWaveNode());
        createSquareWave.setOnAction(e -> createSquareWaveNode());
        createWhiteNoise.setOnAction(e -> createWhiteNoiseNode());
        createVolumeFilter.setOnAction(e -> createVolumeNode());

        primaryStage.setResizable(false);





       /* parent.setVisible(true);
        parent.setStyle("-fx-color: #a0b981; -fx-opacity: .2;");
        //root.setHgap(10);
        //root.setVgap(10);
        //root.setAlignment(Pos.CENTER);
        
        parent.setMinSize(200,200);


        grandParent.setLeft(leftSide);
        grandParent.setCenter(parent);
        //grandParent.setRight(root);

////////////////// SINE WAVE ///////////////////////////////////////////////////////////////////////////////////////////
        /// ROW 0
        // Sine wave label
        Label sineWaveLabel = new Label();
        sineWaveLabel.setText("Sine Wave Generator: ");
        leftSide.getChildren().add(sineWaveLabel);

        // Frequency Text Field
        TextField frequencyField = new TextField();
        frequencyField.setPromptText("Enter a frequency... integers only!");
        leftSide.getChildren().add(frequencyField);

        // Sine wave label
        Label sineWaveCounter = new Label();
        sineWaveCounter.setText("Sine Wave Count: " + sineWaveCount_);
        leftSide.getChildren().add(sineWaveCounter);

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
        leftSide.getChildren().add(createSineWave);

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
        leftSide.getChildren().add(deleteSineWave);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*//*

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
*//*
*/

        primaryStage.setScene(new Scene(grandParent, 1000, 500));
        primaryStage.show();
    }

    private void createVolumeNode() {
        volume Volume = new volume(1);
        AudioComponentWidget node = new AudioComponentWidget(parent, Volume);

    }

    private void createWhiteNoiseNode() {
        AudioComponentWidget node = new AudioComponentWidget(parent, new WhiteNoise());

    }

    private void createSquareWaveNode() {
        AudioComponentWidget node = new AudioComponentWidget(parent, new SquareWave(250));
    }

    private void createSineWaveNode() {
        AudioComponent sineWave = new SineWave(440);
        AudioComponentWidget node = new AudioComponentWidget(parent, sineWave);
        System.out.println(node);
    }


}