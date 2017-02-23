using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    internal class Room
    {
        private readonly string name_; 
        private uint capacity_;
        private uint users_;
        private readonly bool locked_;


        public Room(string name, uint users, uint capacity, bool locked)
        {
            name_ = name;
            users_ = users;
            capacity_ = capacity;
            locked_ = locked;
        }

        public string name()
        {
            return name_;
        }

        public void set_users(uint users)
        {
            users_ = users;
        }

        public uint users()
        {
            return users_;
        }

        public void set_capacity(uint capacity)
        {
            capacity_ = capacity;
        }

        public uint capacity()
        {
            return capacity_;
        }

        public bool locked()
        {
            return locked_;
        }

    }
}
