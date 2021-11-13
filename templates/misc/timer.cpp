#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
   private:
    std::string title;
    std::chrono::high_resolution_clock::time_point start;

   public:
    Timer(std::string t)
        : title(t), start(std::chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(finish -
                                                                  start)
                .count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms
                  << " ms to finish.\n";
    }
};
