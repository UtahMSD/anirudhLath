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

import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import java.util.ArrayList;

public class SynthGUI extends Application {

// Member Variables
    Player player = new Player();


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
        play.setOnAction(e -> {
            try {
                play();
            } catch (LineUnavailableException ex) {
                ex.printStackTrace();
            }
        });


        primaryStage.setScene(new Scene(grandParent, 1000, 500));
        primaryStage.show();
    }

    private void play() throws LineUnavailableException {
        Player.replay(0);
    }

    private void createVolumeNode() {
        volume Volume = new volume(0);
        AudioComponentWidget node = new AudioComponentWidget(parent, Volume);

    }

    private void createWhiteNoiseNode() {
        AudioComponentWidget node = new AudioComponentWidget(parent, new WhiteNoise());

    }

    private void createSquareWaveNode() {
        AudioComponentWidget node = new AudioComponentWidget(parent, new SquareWave(0));
    }

    private void createSineWaveNode() {
        AudioComponent sineWave = new SineWave(0);
        AudioComponentWidget node = new AudioComponentWidget(parent, sineWave);
        System.out.println(node);
    }
}