#ifndef INSTANCE_HPP
#define INSTANCE_HPP

class Instance {

    public:
        virtual void read_from_file() = 0;
        virtual void write_data() = 0;
};

#endif

