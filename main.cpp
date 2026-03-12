#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "filereader.h"
#include "mysha.h"

std::string readHash(const std::string& filename)
{
    std::ifstream in(filename);
    if (!in)
        throw std::runtime_error("Не удалось открыть файл с хэшем");

    std::string s;
    in >> s;
    return s;
}

std::string toHex(const std::vector<uint8_t>& data)
{
    const char* hex = "0123456789abcdef";
    std::string out;

    for (uint8_t b : data)
    {
        out.push_back(hex[b >> 4]);
        out.push_back(hex[b & 0x0F]);
    }
    return out;
}

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        std::cout << "Пример:\n";
        std::cout << "  mysha -h sha256 file.bin\n";
        std::cout << "  mysha -h sha256 -v file.bin hash.txt\n";
        return 1;
    }

    std::string algo = argv[2];
    bool verify = (std::string(argv[3]) == "-v");

    std::string file = verify ? argv[4] : argv[3];
    std::string hashfile = verify ? argv[5] : "";

    try
    {
        FileReader reader(file);
        std::vector<uint8_t> result;

        if (algo == "sha256")
        {
            sha256 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else if (algo == "sha224")
        {
            sha224 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else if (algo == "sha512")
        {
            sha512 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else if (algo == "sha384")
        {
            sha384 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else if (algo == "sha512_256")
        {
            sha512_256 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else if (algo == "sha512_224")
        {
            sha512_224 h;
            while (!reader.eof())
            {
                auto chunk = reader.read();
                if (!chunk.empty())
                    h.update(chunk.data(), chunk.size());
            }
            h.finalize();
            auto d = h.digest();
            result.assign(d.begin(), d.end());
        }
        else
        {
            std::cout << " выбран неверный алгоритм\n";
            return 1;
        }

        std::string hexResult = toHex(result);

        if (verify)
        {
            std::string expected = readHash(hashfile);

            if (hexResult == expected)
                std::cout << "контрольная сумма совпадает\n";
            else
                std::cout << "ошибка - контрольная сумма не совпадает\n";
        }
        else
        {
            std::cout << hexResult << "\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
