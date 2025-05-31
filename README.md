# C++ Bitboard Chess Engine (Work in Progress)

This repository contains the foundational code for a chess engine implemented in C++. The engine utilizes a [Bitboard](https://www.chessprogramming.org/Bitboards) representation for efficient board state management and is being developed incrementally to implement core chess rules and move logic.

## Project Status

This project is currently **in progress**. The core data structures are established, and basic movement logic for several pieces is implemented. The immediate focus is on building out robust move generation, validation, and game state management before moving on to search algorithms and an AI.

## Features

*   **Bitboard Representation:** The board state is efficiently represented using `uint64_t` bitboards for each piece type and color, allowing for fast bitwise operations for move generation and board updates.
*   **Basic Piece Movement Logic:**
    *   **Pawns:** Implemented for single and double-square initial moves (`pawn_development`) and standard diagonal captures (`pawn_capture`). Includes preliminary `enpassant` tracking.
    *   **Rooks:** Handles straight-line horizontal and vertical moves (`rook`) with path obstruction checks.
    *   **Bishops:** Handles diagonal moves (`bishop`) with path obstruction checks.
    *   **Queens:** Combines Rook and Bishop movement logic (`queen`) with path obstruction checks.
    *   **Knights:** Implements L-shaped moves (`knights`) with destination validation.
*   **Piece Capture Logic:** Integrated into piece movement functions, allowing pieces to capture opponent pieces. Handles removal of captured pieces from their respective bitboards.
*   **Piece Lookup:** A `piece_lookup` function identifies which piece (if any) occupies a given square.
*   **Board Visualization:** A `print_board` utility function provides an ASCII representation of the current board state for debugging and viewing. (Note: Ranks are displayed from 8 down to 1, as is common in chess notation, but internally A1 corresponds to the LSB).

## How It Works (Current Implementation)

The engine leverages bitwise operations for high-performance board manipulations:

*   **Board Representation:** Each `uint64_t` in the `Bitboards` struct represents the positions of all pieces of a specific type and color (e.g., `white_pawns` has bits set for every square a white pawn occupies).
*   **Square to Bitboard Mapping:** Squares are mapped to single-bit `uint64_t` values, typically `0x8000000000000000 >> (rank * 8 + file)` for a top-left (A8) to bottom-right (H1) indexing.
*   **Move Functions (`bishop`, `rook`, `queen`, `knights`, `pawn_development`, `pawn_capture`):** These functions take current and destination coordinates. They perform:
    *   **Validation:** Check for valid move patterns (e.g., knight's L-shape, bishop's diagonal).
    *   **Path Checking:** For sliding pieces (Rook, Bishop, Queen), they check if any pieces obstruct the path using `allbits` (a combined bitboard of all pieces).
    *   **Capture Handling:** If the destination square is occupied by an opponent's piece, that piece's bit is unset from its respective bitboard.
    *   **Board Update:** The moving piece's bit is unset from its origin square and set on its destination square.
*   **Game State:** `move_count` tracks the total moves made, and `enpassant` attempts to track the potential for an en passant capture in the next turn (requires careful implementation for full FEN compliance).

## Future Plans

The following are high-priority items for future development:

*   **Comprehensive Move Generation:** Implement a function that generates *all legal moves* for a given board state, rather than just validating a single proposed move.
*   **King Safety & Check Detection:** Implement logic to detect if the King is in check, and filter moves to ensure the King is not left in check or put into check. This is crucial for valid play.
*   **Checkmate and Stalemate Detection:** Build mechanisms to identify terminal game states.
*   **Castling:** Implement the special castling move logic and rules.
*   **Pawn Promotion Options:** Allow the player to choose the promotion piece (Queen, Rook, Bishop, Knight), not just default to Queen.
*   **Draw Conditions:** Add detection for 50-move rule, threefold repetition, and insufficient material.
*   **FEN (Forsyth-Edwards Notation) Parsing/Generation:** To easily load and represent various board states.
*   **UCI (Universal Chess Interface) Protocol:** To allow the engine to communicate with chess GUIs.
*   **AI (Search Algorithm):** Implement a search algorithm (e.g., Minimax with Alpha-Beta Pruning) and evaluation function to enable the engine to play chess.
*   **Perft Testing:** Implement a Perft function for robust testing of move generation.
*   **Refined Error Handling:** More specific and robust error handling for invalid moves or board states.

## Getting Started

### Prerequisites

*   A C++ compiler (e.g., g++).

### Compiling

Navigate to the project root directory and compile the source file:

```bash
g++ -std=c++17 -o chess_engine main.cpp # Replace main.cpp with your actual source file name if different
