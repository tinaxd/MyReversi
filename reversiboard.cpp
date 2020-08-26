#include "reversiboard.h"

ReversiBoard::ReversiBoard(QObject *parent)
    : QObject(parent)
{
    for (size_t i=0; i<64; i++) {
        m_cells.at(i) = DISK_NONE;
    }

    m_cells.at(27) = DISK_WHITE;
    m_cells.at(36) = DISK_WHITE;
    m_cells.at(28) = DISK_BLACK;
    m_cells.at(35) = DISK_BLACK;
    emit changed();
}

ReversiBoard::CountResult ReversiBoard::count() const
{
    CountResult result;
    result.black = 0;
    result.white = 0;
    result.none = 0;
    for (size_t i=0; i<64; i++) {
        switch (m_cells.at(i)) {
        case DISK_BLACK:
            result.black++;
            break;
           case DISK_WHITE:
            result.white++;
            break;
        case DISK_NONE:
            result.none++;
            break;
        }
    }
    return result;
}

ReversiBoard::TestResult ReversiBoard::test(ReversiDisk player, unsigned int position) const
{
    TestResult result;
    if (m_cells.at(position) != DISK_NONE) return result;
    for (const auto& line : straightLines(position)) {
        if (line.size() < 2) continue;
        bool contact = false;
        bool finish = false;
        TestResult buf;
        for (size_t i=1; i<line.size(); i++) {
            const auto& cell = m_cells.at(line.at(i));
            if (!contact) {
                if (cell != player && cell != DISK_NONE) {
                    contact = true;
                    buf.push_back(std::make_tuple(line.at(i), player));
                } else {
                    break;
                }
            } else {
                if (cell != player && cell != DISK_NONE) {
                    buf.push_back(std::make_tuple(line.at(i), player));
                } else if (cell == player) {
                    buf.push_back(std::make_tuple(line.at(i), player));
                    finish = true;
                    break;
                } else {
                    break;
                }
            }
        }

        if (finish) {
            for (auto& elem : buf) result.push_back(move(elem));
        }
    }
    return result;
}

void ReversiBoard::applyTestResult(const ReversiBoard::TestResult &result)
{
    bool changed = false;
    for (const auto& pair : result) {
        changed = true;
        m_cells.at(std::get<0>(pair)) = std::get<1>(pair);
    }
    if (changed) emit this->changed();
}

int ReversiBoard::put(ReversiDisk player, unsigned int position)
{
    const auto& result = test(player, position);
    applyTestResult(result);
    return result.size();
}

ReversiDisk ReversiBoard::get(unsigned int position) const
{
    return m_cells.at(position);
}

ReversiDisk ReversiBoard::get(unsigned int row, unsigned int column) const
{
    return m_cells.at(row * 8 + column);
}

std::vector<std::vector<unsigned int> > ReversiBoard::straightLines(unsigned int basePosition)
{
    std::vector<std::vector<unsigned int>> lines;
    const auto baseRow = basePosition / 8;
    const auto baseColumn = basePosition % 8;
    auto make = [row=baseRow, col=baseColumn](int direction) mutable -> std::vector<unsigned int> {
        std::vector<unsigned int> line;
        while (0 <= row && row < 8 && 0 <= col && col < 8)
        {
            line.push_back(row * 8 + col);
            switch (direction)
            {
                case 0:
                    row--; col--; break;
                case 1:
                    row--; break;
                case 2:
                    row--; col++; break;
                case 3:
                    col--; break;
                case 4:
                    col++; break;
                case 5:
                    row++; col--; break;
                case 6:
                    row++; break;
                case 7:
                    row++; col++; break;
            }
        }
        return line;
    };

    for (int i=0; i<8; i++) lines.push_back(make(i));
    return lines;
}
