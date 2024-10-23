# include "ft_shield.h"

int main() {
    char *program[] = {
        "#include \"ft_shield.h\"",
        "#include <stdio.h>",
        "",
        "int main() {",
        "    char *program[] = {",
        "        \"#include \\\"ft_shield.h\\\"\",",
        "        \"#include <stdio.h>\",",
        "        \"\",",
        "        \"int main() {\",",
        "        \"    char *program[] = {\",",
        "        ",
        "        \"    };\",",
        "        \"    for (int i = 0; i < 17; i++) {\",",
        "        \"        printf(\\\"%s\\n\\\", program[i]);\",",
        "        \"    }\",",
        "        \"    create_service(SERVICE_NAME, DEST_FILE);\",",
        "        \"    create_daemon();\",",
        "        \"    server();\",",
        "        \"    return 0;\",",
        "        \"}\",",
        "    };",
        "    for (int i = 0; i < 17; i++) {",
        "        printf(\"%s\\n\", program[i]);",
        "    }",
        "    create_service(SERVICE_NAME, DEST_FILE);",
        "    create_daemon();",
        "    server();",
        "    return 0;",
        "}",
    };

    for (int i = 0; i < 20; i++) {
        printf("%s\n", program[i]);
    }
    create_service(SERVICE_NAME, DEST_FILE);
    create_daemon();
    server();
    return (0);
}

