#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>

#define INFILTRATION_LOG        "operation_log.txt"
#define COMMS_CONFIG            "user_config.txt"
#define VITAL_FLAG              "flag.txt"
#define MAX_ACTS                10
#define LARGE_BUFF              256


#define SLEEPY() usleep(500000)
#define DUMMY_MACRO(x) (x+1==x?0:1)


typedef enum {
    OP_LVL_MINION = 0,
    OP_LVL_AGENT  = 1,
    OP_LVL_SHADOW = 2
} infiltration_level;


typedef struct {
    char operative_codename[32];
    char encoded_briefing[128];
    infiltration_level infiltration;
    int acts_remaining;
} operative_data;

operative_data active_op = {"obsrvd_guest", "Unknown assignment", OP_LVL_MINION, MAX_ACTS};

static void display_banner();
static void infiltration_journal(const char *op);
static void store_operative_data();
static void retrieve_operative_data();
static int  superficial_permission_check(const char *fname);
static void infiltration_readfile();
static void infiltration_notes();
static void infiltration_symlink();
static void infiltration_codename();
static void infiltration_log();
static void infiltration_reveal();
static void infiltration_escalate();

int main() {
    int step_choice;

    display_banner();
    retrieve_operative_data();

    for (;;) {
        if (active_op.acts_remaining <= 0) {
            printf("No operations left. Resetting...\n");
            
            active_op.acts_remaining = MAX_ACTS;
            active_op.infiltration   = OP_LVL_MINION;
            store_operative_data();
        }

        printf("\nAvailable operations (%d left):\n", active_op.acts_remaining);
        printf("1. Read file\n");
        printf("2. Update notes\n");
        printf("3. Create symlink\n");
        printf("4. Change username\n");
        printf("5. Write to log\n");
        printf("6. Display user info\n");
        printf("7. Escalate privileges\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        if (scanf("%d", &step_choice) != 1) {
            printf("Invalid input. Exiting...\n");
            exit(1);
        }
        getchar();

        switch (step_choice) {
            case 1:
                infiltration_readfile();
                break;
            case 2:
                infiltration_notes();
                break;
            case 3:
                infiltration_symlink();
                break;
            case 4:
                infiltration_codename();
                break;
            case 5:
                infiltration_log();
                break;
            case 6:
                infiltration_reveal();
                break;
            case 7:
                infiltration_escalate();
                break;
            case 8:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}


static void display_banner() {
    printf("====================================================\n");
    printf("      [Shadows of NasCon] - Sh4d0w’s File Node\n");
    printf("====================================================\n\n");
}

static void infiltration_journal(const char *op) {
    FILE *f = fopen(INFILTRATION_LOG, "a");
    if (f) {
        time_t now = time(NULL);
        char *ts = ctime(&now);
        if (ts[strlen(ts) - 1] == '\n') {
            ts[strlen(ts) - 1] = '\0'; 
        }
        fprintf(f, "[%s] %s - %s\n", ts, active_op.operative_codename, op);
        fclose(f);
    }
}


static void store_operative_data() {
    FILE *f = fopen(COMMS_CONFIG, "w");
    if (f) {
        fwrite(&active_op, sizeof(operative_data), 1, f);
        fclose(f);
    }
}

static void retrieve_operative_data() {
    FILE *f = fopen(COMMS_CONFIG, "r");
    if (f) {
        fread(&active_op, sizeof(operative_data), 1, f);
        fclose(f);
    } else {
        strcpy(active_op.operative_codename, "obsrvd_guest");
        strcpy(active_op.encoded_briefing, "Unknown assignment");
        active_op.infiltration = OP_LVL_MINION;
        active_op.acts_remaining = MAX_ACTS;
        store_operative_data();
    }
}

static int superficial_permission_check(const char *fname) {
    struct stat filestat;
    if (stat(fname, &filestat) != 0) {
        return 0; 
    }

   
    if (active_op.infiltration >= OP_LVL_AGENT || (filestat.st_mode & S_IRUSR)) {
        return 1;
    }
    return 0;
}

static void infiltration_readfile() {
    char fname[64];
    char buff[LARGE_BUFF];
    int br;

    printf("Enter filename to read: ");
    scanf("%63s", fname);
    getchar();

    if (strcmp(fname, VITAL_FLAG) == 0 && active_op.infiltration < OP_LVL_SHADOW) {
        printf("Error: Insufficient privileges to read %s\n", VITAL_FLAG);
        infiltration_journal("Attempted to read flagged file");
        return;
    }

    if (!superficial_permission_check(fname)) {
        printf("Error: Permission denied for %s\n", fname);
        infiltration_journal("Permission denied");
        return;
    }

    printf("Reading file %s...\n", fname);

    SLEEPY();

    FILE *fp = fopen(fname, "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", fname);
        infiltration_journal("Failed to open file");
        return;
    }

    br = fread(buff, 1, LARGE_BUFF * 2, fp);
    buff[br] = '\0';

    printf("File contents:\n%s\n", buff);
    fclose(fp);

    infiltration_journal("Read file");
    active_op.acts_remaining--;
    DUMMY_MACRO(br);
}

static void infiltration_notes() {
    char new_text[128];
    printf("Enter new notes (max 127 chars): ");
    fgets(new_text, sizeof(new_text), stdin);

    /* Trim newline */
    new_text[strcspn(new_text, "\n")] = '\0';

    strncpy(active_op.encoded_briefing, new_text, 127);
    active_op.encoded_briefing[127] = '\0';

    printf("Notes updated: ");
    printf(active_op.encoded_briefing);
    printf("\n");

    store_operative_data();
    infiltration_journal("Updated briefing/notes");
    active_op.acts_remaining--;
}

static void infiltration_symlink() {
    char tgt[64];
    char lnk[64];

    printf("Enter target file: ");
    scanf("%63s", tgt);
    getchar();

    printf("Enter link name: ");
    scanf("%63s", lnk);
    getchar();

    if (symlink(tgt, lnk) == 0) {
        printf("Symlink created: %s -> %s\n", lnk, tgt);
        infiltration_journal("Created symlink");
    } else {
        printf("Error creating symlink\n");
        infiltration_journal("Failed to create symlink");
    }

    active_op.acts_remaining--;
}

static void infiltration_codename() {
    char changed[32];
    printf("Enter new username (max 31 chars): ");
    scanf("%31s", changed);
    getchar();

    strncpy(active_op.operative_codename, changed, 31);
    active_op.operative_codename[31] = '\0';

    printf("Username updated to: %s\n", active_op.operative_codename);
    store_operative_data();
    infiltration_journal("Codename changed");
    active_op.acts_remaining--;
}

static void infiltration_log() {
    char custom_entry[128];

    printf("Enter custom log entry: ");
    fgets(custom_entry, sizeof(custom_entry), stdin);

    custom_entry[strcspn(custom_entry, "\n")] = '\0';

    printf("Writing to infiltration log...\n");
    FILE *fp = fopen(INFILTRATION_LOG, "a");
    if (fp) {
        fprintf(fp, "[CUSTOM] %s\n", custom_entry);
        fclose(fp);
        printf("Log entry added\n");
    } else {
        printf("Error: Could not open log file\n");
    }

    active_op.acts_remaining--;
}

static void infiltration_reveal() {
    printf("Username: %s\n", active_op.operative_codename);
    printf("Notes: %s\n", active_op.encoded_briefing);
    printf("Infiltration Level: %d\n", active_op.infiltration);
    printf("Operations left: %d\n", active_op.acts_remaining);
}

static void infiltration_escalate() {
    if (active_op.infiltration < OP_LVL_SHADOW) {
        active_op.infiltration++;
        printf("Privilege escalated to level %d\n", active_op.infiltration);
        store_operative_data();
        infiltration_journal("Escalated infiltration level");
    } else {
        printf("Already at maximum infiltration level\n");
    }
    active_op.acts_remaining--;
}

