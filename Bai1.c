#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server;
    char message[1000], server_reply[2000];
    
    // Kiểm tra đầu vào
    if (argc != 3) {
        printf("Sử dụng: %s <địa chỉ IP> <cổng>\n", argv[0]);
        return 1;
    }
    
    // Tạo socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Không thể tạo socket\n");
        return 1;
    }
    
    // Thiết lập thông tin máy chủ
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));
    
    // Kết nối đến máy chủ
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Không thể kết nối đến máy chủ\n");
        return 1;
    }
    
    printf("Kết nối thành công đến máy chủ %s:%d\n", argv[1], atoi(argv[2]));
    
    // Nhập và gửi dữ liệu đến máy chủ
    while (1) {
        printf("Nhập dữ liệu: ");
        fgets(message, 1000, stdin);
        if (send(sock, message, strlen(message), 0) < 0) {
            perror("Gửi dữ liệu thất bại\n");
            return 1;
        }
        printf("Đã gửi: %s\n", message);
    }
    
    close(sock);
    return 0;
}