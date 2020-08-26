#ifndef REVERSIBOARD_H
#define REVERSIBOARD_H

#include <array>
#include <vector>
#include <tuple>
#include <QObject>


enum ReversiDisk
{
    DISK_BLACK,
    DISK_WHITE,
    DISK_NONE
};

class ReversiBoard : public QObject
{
    Q_OBJECT

public:
    ReversiBoard(QObject *parent = nullptr);

    using TestResult = std::vector<std::tuple<unsigned int, ReversiDisk>>;

    struct CountResult
    {
        unsigned int black;
        unsigned int white;
        unsigned int none;
    };

    CountResult count() const;
    TestResult test(ReversiDisk player, unsigned int position) const;
    void applyTestResult(const TestResult& result);
    int put(ReversiDisk player, unsigned int position);

    ReversiDisk get(unsigned int position) const;
    ReversiDisk get(unsigned int row, unsigned int column) const;

private:
    std::array<ReversiDisk, 64> m_cells;

    static std::vector<std::vector<unsigned int>> straightLines(unsigned int position);

signals:
    void changed();
};

#endif // REVERSIBOARD_H
