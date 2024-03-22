class Color {
public:
    // Default constructor 
    Color() : red(0), green(0), blue(0), transparency(255) {} // Default to fully opaque black


    // Constructor
    Color(int r, int g, int b, int alpha) : red(r), green(g), blue(b), transparency(alpha) {}

    // Allowed colors
    enum NamedColor {
        WHITE,
        BLACK,
        RED,
        GREEN,
        BLUE

    };

    Color getColorFromNamedColor(NamedColor namedColor) {
        switch (namedColor) {
        case WHITE:
            return Color{ 255, 255, 255, 255 };
        case BLACK:
            return Color{ 0, 0, 0, 255 };
        case RED:
            return Color{ 255, 0, 0, 255 };
        case GREEN:
            return Color{ 0, 255, 0, 255 };
        case BLUE:
            return Color{ 0, 0, 255, 255 };
        default:
            // Handle invalid named color
            // You could throw an exception or return a default color
            return { 0, 0, 0, 255 }; // Default to fully opaque black
        }
    }



private:
    int red;
    int green;
    int blue;
    int transparency;


};