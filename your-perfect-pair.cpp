#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

struct Recommendation {
    string faceShape;
    vector<string> observations;
    vector<pair<string, string>> frameStyles;
    string frameWidth;
    string lensHeight;
    string bridge;
    string fitNotes;
    vector<pair<string, string>> colors;
    vector<pair<string, string>> lenses;
    vector<string> avoid;
};

string lower(string value) {
    transform(value.begin(), value.end(), value.begin(),
              [](unsigned char character) { return static_cast<char>(tolower(character)); });
    return value;
}

int readNumber(const string& prompt, int minimum, int maximum) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minimum && value <= maximum) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a number from " << minimum << " to " << maximum << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readLine(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void printLine() {
    cout << "\n------------------------------------------------------------\n";
}

Recommendation makeRecommendation(const string& faceShape, const string& skinTone,
                                   const string& useCase, int prescriptionStrength) {
    Recommendation result;
    result.faceShape = faceShape;

    if (faceShape == "Oval") {
        result.observations = {"Face length is slightly greater than its width.",
                               "The jawline appears softly rounded.",
                               "Proportions are naturally balanced."};
        result.frameStyles = {{"Soft rectangles", "Add definition while keeping your natural balance."},
                              {"Classic wayfarers", "Give the face a little structure without overpowering it."},
                              {"Rounded metal frames", "Echo the softer jawline for an easy everyday look."}};
        result.avoid = {"Frames that are much narrower than your cheekbones", "Very heavy oversized frames"};
    } else if (faceShape == "Round") {
        result.observations = {"Face width and length are fairly similar.",
                               "The cheek and jaw lines look softly curved.",
                               "Angular contrast will add definition."};
        result.frameStyles = {{"Angular rectangles", "Sharper lines balance softer facial curves."},
                              {"Browline frames", "A stronger upper edge adds visual lift."},
                              {"Geometric frames", "Crisp angles create flattering contrast."}};
        result.avoid = {"Very small round frames", "Frames with a low, narrow bridge"};
    } else if (faceShape == "Square") {
        result.observations = {"Forehead, cheeks, and jaw have similar widths.",
                               "The jawline has a clear, defined shape.",
                               "Curved lines will soften the overall impression."};
        result.frameStyles = {{"Rounded rectangles", "Keep structure while softening strong angles."},
                              {"Oval frames", "Create a smooth contrast with the jawline."},
                              {"Thin metal frames", "Add polish without adding visual weight."}};
        result.avoid = {"Very boxy frames with thick corners", "Frames wider than your face"};
    } else if (faceShape == "Heart") {
        result.observations = {"The forehead is wider than the lower face.",
                               "Cheekbones are a noticeable feature.",
                               "The chin and jaw taper more narrowly."};
        result.frameStyles = {{"Bottom-heavy frames", "Add visual balance to the lower face."},
                              {"Light oval frames", "Keep the upper face feeling open."},
                              {"Rimless frames", "Offer a subtle look with very little weight."}};
        result.avoid = {"Very top-heavy frames", "Very high, thick browlines"};
    } else if (faceShape == "Diamond") {
        result.observations = {"Cheekbones are the strongest horizontal feature.",
                               "The forehead and jaw taper more narrowly.",
                               "Curved or lifted lines complement the cheekbones."};
        result.frameStyles = {{"Cat-eye frames", "Lift the eye line and complement prominent cheeks."},
                              {"Oval frames", "Soften the angular proportions."},
                              {"Browline frames", "Draw attention upward in a balanced way."}};
        result.avoid = {"Very narrow frames", "Frames that end exactly at the widest cheek point"};
    } else {
        result.observations = {"The face appears longer than it is wide.",
                               "The cheek and jaw lines are relatively straight.",
                               "Deeper frames can add proportion and balance."};
        result.frameStyles = {{"Deep rectangular frames", "Add visual depth to a longer face."},
                              {"Oversized round frames", "Bring width and softness to the proportions."},
                              {"Low-bridge styles", "Help the frame sit comfortably and securely."}};
        result.avoid = {"Very shallow lens heights", "Extremely narrow frames"};
    }

    result.frameWidth = "132-138 mm";
    result.lensHeight = "38-44 mm";
    result.bridge = "18-20 mm";
    result.fitNotes = "The frame should sit level, with your pupils near the centre of each lens and no pressure at the temples.";

    string tone = lower(skinTone);
    if (tone.find("warm") != string::npos) {
        result.colors = {{"Warm tortoiseshell", "Rich contrast with golden warmth."},
                         {"Honey brown", "Soft and easy for everyday wear."},
                         {"Olive", "A muted colour that still feels distinctive."},
                         {"Brushed gold", "Adds warmth without looking too bright."}};
    } else if (tone.find("cool") != string::npos) {
        result.colors = {{"Cool tortoiseshell", "Adds depth without yellow undertones."},
                         {"Charcoal", "A polished alternative to solid black."},
                         {"Deep navy", "A quiet colour with flattering contrast."},
                         {"Silver", "Works cleanly with cooler undertones."}};
    } else {
        result.colors = {{"Soft black", "A dependable choice with clear definition."},
                         {"Neutral tortoiseshell", "Adds texture while staying versatile."},
                         {"Clear crystal", "Keeps the look light and modern."},
                         {"Champagne metal", "A balanced metallic that is easy to wear."}};
    }

    result.lenses = {{"Anti-reflective coating", "Useful for screen work, photos, and night-time glare."},
                     {"UV protection", "A sensible everyday protection feature for outdoor use."},
                     {"High-index lenses", prescriptionStrength >= 4
                                                ? "Worth discussing with an optician for a stronger prescription."
                                                : "Ask an optician whether the thinner profile benefits your prescription."}};

    if (lower(useCase).find("sport") != string::npos) {
        result.lenses.push_back({"Impact-resistant material", "A practical option for active use; confirm the right material with an optician."});
    }

    return result;
}

void printRecommendation(const Recommendation& result) {
    printLine();
    cout << "YOUR PERFECT PAIR\n";
    printLine();
    cout << "Face shape: " << result.faceShape << "\n\n";

    cout << "What we noticed\n";
    for (const string& observation : result.observations) cout << "  - " << observation << '\n';

    cout << "\nRecommended frame styles\n";
    for (const auto& style : result.frameStyles)
        cout << "  - " << style.first << ": " << style.second << '\n';

    cout << "\nStarting size range\n";
    cout << "  Frame width: " << result.frameWidth << '\n';
    cout << "  Lens height: " << result.lensHeight << '\n';
    cout << "  Bridge: " << result.bridge << '\n';
    cout << "  Fit note: " << result.fitNotes << '\n';

    cout << "\nColour palette\n";
    for (const auto& color : result.colors)
        cout << "  - " << color.first << ": " << color.second << '\n';

    cout << "\nLens and comfort options\n";
    for (const auto& lens : result.lenses)
        cout << "  - " << lens.first << ": " << lens.second << '\n';

    cout << "\nTry to avoid\n";
    for (const string& item : result.avoid) cout << "  - " << item << '\n';

    printLine();
    cout << "This is style guidance, not medical or optometry advice. "
            "Confirm prescription and lens choices with a qualified optician.\n";
}

int main() {
    cout << "YOUR PERFECT PAIR\n";
    cout << "Personalised glasses recommendations\n";
    cout << "\nThis local C++ version uses your answers rather than analysing a photo.\n";

    const vector<string> shapes = {"Oval", "Round", "Square", "Heart", "Diamond", "Oblong"};
    const vector<string> tones = {"Warm", "Cool", "Neutral"};

    cout << "\nChoose the face shape that most closely matches you:\n";
    for (size_t index = 0; index < shapes.size(); ++index)
        cout << "  " << index + 1 << ". " << shapes[index] << '\n';
    int shapeChoice = readNumber("Selection: ", 1, static_cast<int>(shapes.size()));

    cout << "\nChoose your skin undertone:\n";
    for (size_t index = 0; index < tones.size(); ++index)
        cout << "  " << index + 1 << ". " << tones[index] << '\n';
    int toneChoice = readNumber("Selection: ", 1, static_cast<int>(tones.size()));

    string useCase = readLine("\nWhat are the glasses mostly for? ");
    string prescription = readLine("Prescription strength, if known (press Enter to skip): ");
    int prescriptionStrength = 0;
    if (!prescription.empty()) {
        try {
            prescriptionStrength = abs(stoi(prescription));
        } catch (...) {
            prescriptionStrength = 0;
        }
    }

    Recommendation recommendation = makeRecommendation(
        shapes[shapeChoice - 1], tones[toneChoice - 1], useCase, prescriptionStrength);
    printRecommendation(recommendation);

    return 0;
}