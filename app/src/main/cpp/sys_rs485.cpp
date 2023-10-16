
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <android/log.h>

#include "sGpio.h"
#include "DnakeFifo.h"
#include "sys_rs485.h"

__sys_rs485 sys_rs485;

static void *sys_rs485_thread(void *) {
    sys_rs485.process();
    return NULL;
}

__sys_rs485::__sys_rs485() {
    m_used = 0;
    m_tty = -1;
    pthread_mutex_init(&m_mutex, NULL);
}

__sys_rs485::~__sys_rs485() {
}

//入口
int __sys_rs485::start(void) {
    int ok = 0;

    {//dnake多系统判断，主要判断是否该机型带有485，如有ok=1
        ok = 1;
    }


    if (ok) {
        const char *tty = "/dev/ttyS3";

        sGpio io;
        io.start("rk", "rs485-de");
        io.dir("rk", "rs485-de", 1);
        io.set("rk", "rs485-de", 0);

        m_tty = ::open(tty, O_RDWR | O_NOCTTY | O_NDELAY);
        if (m_tty < 0) {
            fprintf(stderr, "__sys_rs485::__sys_rs485 open %s error.\n", tty);
            __android_log_print(ANDROID_LOG_INFO, "Test485", "TTY %s open error, return code %d", tty, m_tty);
        } else {
            this->setup(0, 3);
            __android_log_print(ANDROID_LOG_INFO, "Test485", "TTY %s open success ", tty);
        }

        pthread_t pid;
        if (pthread_create(&pid, NULL, sys_rs485_thread, NULL) != 0) {
            perror("__sys_rs485::__sys_rs485 pthread_create\n");
        }
    }
    return 0;
}

//其他机型，485接在单片机上，单片机通过串口和cpu连接
int __sys_rs485::tx(uint8_t *data, int length) {
    return length;
}

int __sys_rs485::rx(uint8_t *data, int length, int timeout) {
    m_used = 1;

    struct timeval tv;
    gettimeofday(&tv, NULL);

    m_rx.flush();
    while (1) {
        usleep(10 * 1000);
        if (m_rx.used() >= length || __ts(tv) >= timeout)
            break;
    }
    int n = m_rx.used() > length ? length : m_rx.used();
    m_rx.get(data, n);
    m_used = 0;
    return n;
}

void __sys_rs485::setup(int pb, int br) {
    if (m_tty < 0)
        return;

    struct termios opt;
    bzero(&opt, sizeof(opt));
    opt.c_cflag |= CLOCAL | CREAD;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cc[VTIME] = 0;
    opt.c_cc[VMIN] = 0;
    switch (pb) {
        case 0: //无校验
            opt.c_cflag &= ~PARENB;
            break;
        case 1: //偶校验
            opt.c_cflag |= PARENB;
            opt.c_cflag &= ~PARODD;
            break;
        case 2: //奇校验
            opt.c_cflag |= PARENB;
            opt.c_cflag |= PARODD;
            break;
    }

    switch (br) {
        case 0:
            cfsetispeed(&opt, B1200);
            cfsetospeed(&opt, B1200);
            break;
        case 1:
            cfsetispeed(&opt, B2400);
            cfsetospeed(&opt, B2400);
            break;
        case 2:
            cfsetispeed(&opt, B4800);
            cfsetospeed(&opt, B4800);
            break;
        case 3:
            cfsetispeed(&opt, B9600);
            cfsetospeed(&opt, B9600);
            break;
        case 4:
            cfsetispeed(&opt, B19200);
            cfsetospeed(&opt, B19200);
            break;
        case 5:
            cfsetispeed(&opt, B38400);
            cfsetospeed(&opt, B38400);
            break;
        case 6:
            cfsetispeed(&opt, B57600);
            cfsetospeed(&opt, B57600);
            break;
        case 7:
            cfsetispeed(&opt, B115200);
            cfsetospeed(&opt, B115200);
            break;
    }
    tcflush(m_tty, TCIFLUSH);
    tcsetattr(m_tty, TCSANOW, &opt);
    fcntl(m_tty, F_SETFL, 0);
}

void __sys_rs485::process(void) {
    DnakeFifo rx;
    fd_set rfds;
    struct timeval tv;

    while (1) {
        int ok = 0;

        FD_ZERO(&rfds);
        FD_SET(m_tty, &rfds);
        tv.tv_sec = 0;
        tv.tv_usec = 20 * 1000;
        ::select(m_tty + 1, &rfds, NULL, NULL, &tv);
        if (FD_ISSET(m_tty, &rfds)) {
            AutoMutex m(&m_mutex);

            uint8_t d[128];
            int r = ::read(m_tty, d, sizeof(d));
            if (r > 0) {
                rx.put(d, r);
                if (rx.used() > 64)
                    ok = 1;
            }
        } else {
            ok = 1;
        }
        if (ok && rx.used()) {
            //读取到485数据，dnake处理逻辑，客户可自行处理
            // vt_uart.rx((uint8_t *)rx.data(), rx.used());
            // sys_aio.rx((uint8_t *)rx.data(), rx.used());
            {//for debug
                fprintf(stderr, "<-- ");
                int length = rx.used();
                uint8_t *data = (uint8_t *) rx.data();
                for (int i = 0; i < length; i++)
                    fprintf(stderr, "%02X ", data[i]);
                fprintf(stderr, "\n");

                __android_log_print(ANDROID_LOG_INFO, "Test485", "<-- RX %02X ...", data[0]);
            }
            rx.flush();
        }
    }
}

//485发送处理
int __sys_rs485::dtx(uint8_t *data, int length) {
    if (m_tty < 0)
        return 0;

    AutoMutex m(&m_mutex);

    sGpio io;
    if (1) {
        io.set("rk", "rs485-de", 1);
    }

    int sz = ::write(m_tty, data, length);

    uint16_t n = 0;
    while (++n) {
        int lsr = 0;
        if (::ioctl(m_tty, TIOCSERGETLSR, &lsr) < 0) {
            break;
        }
        if (lsr & TIOCSER_TEMT) {
            //延时,等最后一字节发送完
            usleep(2 * 1000);
            break;
        }
    }

    if (1) {
        io.set("rk", "rs485-de", 0);
        tcflush(m_tty, TCIFLUSH); //清空缓冲垃圾数据
    }
    return sz;
}
