class TTTBoard(object):
    def __init__(self):
        self.board = [[' ' for _ in range(3)] for _ in range(3)]

    def prettyprint(self):
        boardout = """    |   |
  {} | {} | {}
----+---+----
  {} | {} | {}
----+---+----
  {} | {} | {}
    |   |"""

        print(boardout.format(*[item for sub in self.board for item in sub]))

tttb = TTTBoard()

max_score = 10
min_score = -max_score
def minimax(board, depth, maxdepth):
    maxing_player = depth % 2 == 0
    if depth >= maxdepth or board.gameIsOver():
        if maxing_player:
            return max_score - depth
        else:
            return min_score + depth

    if maxing_player:
        val = min_score

        moves = board.getNextMoves()
        for move in moves:
            newVal = minimax(board.stepped(move), depth + 1, maxdepth)
            val = max(val, newVal)

        return val
    else:
        val = max_score

        moves = board.getNextMoves()
        for move in moves:
            newVal = minimax(board.stepped(move), depth + 1, maxdepth)
            val = min(val, newVal)

        return val
