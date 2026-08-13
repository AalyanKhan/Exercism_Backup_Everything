namespace hellmath {

// TODO: Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
    
    enum class AccountStatus {
    troll,
    guest,
    user,
    mod
    };
    
// TODO: Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.

    enum class Action {
    read,
    write,
    remove
    };

// TODO: Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.

    bool display_post(AccountStatus poster, AccountStatus viewer) {
    return (poster != AccountStatus::troll) || (viewer == AccountStatus::troll);
    }

// TODO: Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.

    bool permission_check(Action action, AccountStatus status) {
        switch (status) {
            case AccountStatus::mod:
                return true; // Mods can do everything (read, write, remove)
                
            case AccountStatus::user:
            case AccountStatus::troll:
                // Both users and trolls can read and write, but not remove
                return action == Action::read || action == Action::write;
                
            case AccountStatus::guest:
                return action == Action::read; // Guests can only read
                
            default:
                return false;
        }
    }

// TODO: Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.

    bool valid_player_combination(AccountStatus usera, AccountStatus userb) {
        if (usera == AccountStatus::guest || userb == AccountStatus::guest) {
            return false; // Guests are completely denied access
        }
        if (usera == AccountStatus::troll || userb == AccountStatus::troll) {
            return usera == AccountStatus::troll && userb == AccountStatus::troll; // Trolls only with trolls
        }
        return true; // Unrestricted for normal users and mods
    }

// TODO: Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
    bool has_priority(AccountStatus user1, AccountStatus user2) {
        // Assign numeric weight based on instructions: mod > user > guest > troll
        int p1 = 0;
        int p2 = 0;

        // Convert the first user's status to a number ranking
        switch (user1) {
            case AccountStatus::mod:   p1 = 4; break;
            case AccountStatus::user:  p1 = 3; break;
            case AccountStatus::guest: p1 = 2; break;
            case AccountStatus::troll: p1 = 1; break;
        }

        // Convert the second user's status to a number ranking
        switch (user2) {
            case AccountStatus::mod:   p2 = 4; break;
            case AccountStatus::user:  p2 = 3; break;
            case AccountStatus::guest: p2 = 2; break;
            case AccountStatus::troll: p2 = 1; break;
        }

        // Returns true only if p1 is strictly larger than p2
        return p1 > p2;
    }

}  // namespace hellmath
