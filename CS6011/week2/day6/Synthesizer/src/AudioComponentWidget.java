import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.control.Button;
import javafx.scene.control.Slider;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Line;
import javafx.scene.text.Text;

import java.util.ArrayList;

public class AudioComponentWidget extends Pane {

    HBox node;
    private AnchorPane parent_;
    private AudioComponent audioComponent_;
    ArrayList<Line> lines_ = new ArrayList<>();
    Circle outputCircle;
    Line line = new Line();


    public AudioComponentWidget(AnchorPane parent, AudioComponent audioComponent) {
        node = new HBox();
        parent_ = parent;
        audioComponent_ = audioComponent;

        VBox leftColumn = new VBox();
        VBox centerColumn = new VBox();
        VBox rightColumn = new VBox();
        int frequency = 0;


        node.setStyle("-fx-background-color: white; -fx-border-width: 1px; -fx-border-color: darkgrey; " +
                "-fx-border-radius: 5px; -fx-background-radius: 5px");

        // Left Column
        if (audioComponent_.hasInput()) {
            Circle inputCircle = new Circle(5);
            inputCircle.setFill(Color.BLUE);
            leftColumn.setAlignment(Pos.CENTER_LEFT);
            leftColumn.setSpacing(5);
            leftColumn.setPadding(new Insets(5, 5, 5, 5));
            leftColumn.getChildren().add(inputCircle);
            node.getChildren().add(leftColumn);
        }

        // Center Column
        Text nodeText = new Text();

        Slider frequencySlider = new Slider();
        if (audioComponent_.hasFrequency()) {
            nodeText = new Text(audioComponent_.getLabel() + " - " + Integer.toString(frequency));
            centerColumn.getChildren().add(nodeText);
            centerColumn.getChildren().add(frequencySlider);

        } else {
            nodeText = new Text(audioComponent_.getLabel());
            centerColumn.getChildren().add(nodeText);
        }
        centerColumn.setAlignment(Pos.CENTER);
        centerColumn.setSpacing(5);
        centerColumn.setPadding(new Insets(5, 5, 5, 5));
        node.getChildren().add(centerColumn);

        // Right Column
        Button deleteNodeButton = new Button("x");
        deleteNodeButton.setMaxSize(Double.MIN_VALUE, Double.MIN_VALUE);
        outputCircle = new Circle(5);
        outputCircle.setFill(Color.GREEN);
        rightColumn.setAlignment(Pos.CENTER_RIGHT);
        rightColumn.setSpacing(5);
        rightColumn.setPadding(new Insets(5, 5, 5, 5));
        rightColumn.getChildren().add(deleteNodeButton);
        rightColumn.getChildren().add(outputCircle);
        node.getChildren().add(rightColumn);

        // Close Button
        deleteNodeButton.setOnAction(e -> close());

        // Node
        nodeText.setOnMouseDragged(e -> moveWidget(e));
        outputCircle.setOnMouseDragged(e -> drawLine(e));


        // Parent
        AnchorPane.setTopAnchor(node, 50.0);
        AnchorPane.setLeftAnchor(node, 50.0);
        this.getChildren().add(node);
        parent_.getChildren().add(line);
        parent_.getChildren().add(this);


    }

    private void drawLine(MouseEvent e) {
        Bounds outputCircleBounds = outputCircle.localToScene(outputCircle.getBoundsInLocal());
        Bounds speakerBounds = SynthGUI.speaker_.localToScene(SynthGUI.speaker_.getBoundsInLocal());
        Bounds bounds = parent_.getBoundsInParent();

        line.setFill(Color.BLACK);
        line.setStartX(outputCircleBounds.getMinX() - bounds.getMinX());
        line.setStartY(outputCircleBounds.getMinY() - bounds.getMinY());
        double speakerDistance = Math.sqrt(Math.pow(e.getSceneX() - speakerBounds.getCenterX(), 2) + Math.pow(e.getSceneY() - speakerBounds.getCenterY(), 2));
        if (speakerDistance < 20.0) {
            line.setEndX(e.getSceneX() - bounds.getMinX());
            line.setEndY(e.getSceneY() - bounds.getMinY());
        } else {
            for (Node node)
            double distance = Math.sqrt(Math.pow(e.getSceneX() - speakerBounds.getCenterX(), 2) + Math.pow(e.getSceneY() - speakerBounds.getCenterY(), 2));

        }



    }

    private void moveWidget(MouseEvent e) {
        Bounds bound = parent_.getBoundsInParent();
        Bounds outputCirleBounds = outputCircle.localToScene(outputCircle.getBoundsInLocal());
        AnchorPane.setTopAnchor(this, e.getSceneY() - bound.getMinY());
        AnchorPane.setLeftAnchor(this, e.getSceneX() - bound.getMinX());
        line.setStartX(outputCirleBounds.getMinX() - bound.getMinX());
        line.setStartY(outputCirleBounds.getMinY() - bound.getMinY());
    }

    private void close() {
        System.out.println(this);
        parent_.getChildren().remove(this);

    }

}
