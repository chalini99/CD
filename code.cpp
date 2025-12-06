#include <iostream>
#include <vector>
#include <regex>
#include <string>
using namespace std;

// -------------------- 1. LEXICAL ANALYSIS --------------------
vector<pair<string, string>> lexicalAnalysis(const string &code) {
    vector<pair<string, string>> tokens;

    regex tokenPattern(
        R"((\d+)|([A-Za-z_]\w*)|(\+)|(-)|(\*)|(/)|(=)|(;))"
    );

    auto words_begin = sregex_iterator(code.begin(), code.end(), tokenPattern);
    auto words_end = sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        smatch match = *it;
        string value = match.str();

        if (regex_match(value, regex("\\d+"))) tokens.push_back({"NUMBER", value});
        else if (regex_match(value, regex("[A-Za-z_]\\w*"))) tokens.push_back({"ID", value});
        else if (value == "+") tokens.push_back({"PLUS", value});
        else if (value == "-") tokens.push_back({"MINUS", value});
        else if (value == "*") tokens.push_back({"MUL", value});
        else if (value == "/") tokens.push_back({"DIV", value});
        else if (value == "=") tokens.push_back({"ASSIGN", value});
        else if (value == ";") tokens.push_back({"SEMI", value});
    }

    return tokens;
}

// AST structure
struct AST {
    string assign_to;
    string left;
    string op;
    string right;
};

// -------------------- 2. SYNTAX ANALYSIS --------------------
AST syntaxAnalysis(const vector<pair<string,string>> &tokens) {
    AST ast;
    ast.assign_to = tokens[0].second;
    ast.left = tokens[2].second;
    ast.op = tokens[3].second;
    ast.right = tokens[4].second;
    return ast;
}

// -------------------- 3. SEMANTIC ANALYSIS --------------------
string semanticAnalysis(const AST &ast) {
    if (!regex_match(ast.assign_to, regex("[A-Za-z_]\\w*"))) 
        return "Semantic Error: invalid variable name";
    
    return ast.assign_to + " = " + ast.left + " " + ast.op + " " + ast.right;
}

// -------------------- 4. INTERMEDIATE CODE --------------------
vector<string> intermediateCode(const AST &ast) {
    vector<string> ir;
    ir.push_back("t1 = " + ast.left + " " + ast.op + " " + ast.right);
    ir.push_back(ast.assign_to + " = t1");
    return ir;
}

// -------------------- 5. OPTIMIZATION --------------------
string optimize(const vector<string> &ir) {
    string operation = ir[0].substr(ir[0].find("=") + 2);
    return ir[1].substr(0, ir[1].find("=")) + "= " + operation;
}

// -------------------- 6. CODE GENERATION --------------------
vector<string> codeGen(const AST &ast) {
    vector<string> code;
    code.push_back("MOV R1, " + ast.left);
    code.push_back("MOV R2, " + ast.right);

    if (ast.op == "+") code.push_back("ADD R1, R2");
    else if (ast.op == "-") code.push_back("SUB R1, R2");
    else if (ast.op == "*") code.push_back("MUL R1, R2");
    else if (ast.op == "/") code.push_back("DIV R1, R2");

    code.push_back("MOV " + ast.assign_to + ", R1");
    return code;
}

// -------------------- MAIN --------------------
int main() {
    string input;
    cout << "Enter an instruction (ex: c = a + 5): ";
    getline(cin, input);

    // PHASE 1
    cout << "\n--- PHASE 1: LEXICAL ANALYSIS ---\n";
    auto tokens = lexicalAnalysis(input);
    for (auto &t : tokens) 
        cout << "(" << t.first << ", " << t.second << ")\n";

    // PHASE 2
    cout << "\n--- PHASE 2: SYNTAX ANALYSIS (AST) ---\n";
    AST ast = syntaxAnalysis(tokens);
    cout << "Assign to: " << ast.assign_to << "\n";
    cout << "Left: " << ast.left << "\n";
    cout << "Operator: " << ast.op << "\n";
    cout << "Right: " << ast.right << "\n";

    // PHASE 3
    cout << "\n--- PHASE 3: SEMANTIC ANALYSIS ---\n";
    cout << semanticAnalysis(ast) << "\n";

    // PHASE 4
    cout << "\n--- PHASE 4: INTERMEDIATE CODE (3AC) ---\n";
    auto ir = intermediateCode(ast);
    for (auto &line : ir) cout << line << "\n";

    // PHASE 5
    cout << "\n--- PHASE 5: OPTIMIZATION ---\n";
    cout << optimize(ir) << "\n";

    // PHASE 6
    cout << "\n--- PHASE 6: CODE GENERATION ---\n";
    auto asmCode = codeGen(ast);
    for (auto &line : asmCode) cout << line << "\n";

    return 0;
}
