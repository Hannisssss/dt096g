//
// Created by Hanna Sjöström on 2025-03-09.
//

#ifndef LABB1_PRINT_H
#define LABB1_PRINT_H
#include <iostream>
#include <memory>
#include <vector>
#include "ASTNode.h"

void printTree(const ASTNodePtr& node, int depth = 0) {
    if (node == nullptr) return;

    // Skapa indentering beroende på djupet
    std::string indent(depth * 2, ' ');

    // Kolla vilken typ av nod vi har och skriv ut information
    if (auto charNode = dynamic_cast<CHARNode*>(node.get())) {
        std::cout << indent << "CHAR: '" << charNode->value << "'\n";
    }
    else if (auto starNode = dynamic_cast<STARNode*>(node.get())) {
        std::cout << indent << "STARNode (*)\n";
        printTree(starNode->factor, depth + 1);  // Rekursivt skriv ut barnet
    }
    else if (auto anyNode = dynamic_cast<ANYNode*>(node.get())) {
        std::cout << indent << "ANYNode (.)\n";
    }
    else if (auto countNode = dynamic_cast<COUNTNode*>(node.get())) {
        std::cout << indent << "COUNTNode { " << countNode->count << " }\n";
        printTree(countNode->factor, depth + 1);  // Rekursivt skriv ut faktorn
    }
    else if (auto orNode = dynamic_cast<ORNode*>(node.get())) {
        std::cout << indent << "ORNode (+)\n";
        printTree(orNode->left, depth + 1);  // Skriv ut vänstergren
        printTree(orNode->right, depth + 1);  // Skriv ut högergren
    }
    else if (auto concatNode = dynamic_cast<CONCATNode*>(node.get())) {
        std::cout << indent << "CONCATNode\n";
        for (const auto& child : concatNode->children) {
            printTree(child, depth + 1);  // Skriv ut varje barn i concatNode
        }
    }
    else if (auto groupNode = dynamic_cast<GROUPNode*>(node.get())) {
        std::cout << indent << "GROUPNode ( )\n";
        printTree(groupNode->expr, depth + 1);  // Skriv ut uttrycket inuti gruppen
    }
    else {
        std::cout << indent << "Unknown Node\n";
    }
}

#endif //LABB1_PRINT_H
