#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <getopt.h>
#include <fcntl.h>
#include <time.h>
#include <sys/ioctl.h>
#include <linux/ioctl.h>
#include <sys/stat.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/* TEMP */
#define	SPI_TX_OCTAL	        0x2000
#define	SPI_RX_OCTAL            0x4000

/* Master H/W CFG */
#define _T_SPI_CPHA_CPOL       0
#define _T_SPI_MODE            (SPI_NO_CS | SPI_RX_DUAL | _T_SPI_CPHA_CPOL)
#define _T_SPI_DATA_RATE       (1000000U)
#define _T_SPI_NO_OF_BITS      (8)
#define _T_SPI_DEVICE_NAME      "/dev/spidev0.1"

/* Slave specific data */
#define DATA_BUFFER_SIZE			2205
#define DATA_BUFFER_SAMPLE_SIZE		(DATA_BUFFER_SIZE * 2)
#define SPI_NO_OF_BYTES_TO_TX		(DATA_BUFFER_SAMPLE_SIZE * 2)

static uint32_t     _spi__Mode          = _T_SPI_MODE;
static uint32_t     _spi__DataRate      = _T_SPI_DATA_RATE;
static uint8_t      _spi__NoOfBits      = _T_SPI_NO_OF_BITS;

static int SPI_HAL_ReceiveData(int spi_fd, uint8_t *rx_buff, size_t data_len);

int main() {

    int spi_Handle;
    spi_Handle = open(_T_SPI_DEVICE_NAME, O_RDWR);
    if(spi_Handle < 0) {
        printf("Error opening device\n");
        return 0;
    }

    int ret_Code = 0;

    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_MODE32, &_spi__Mode);
    if(ret_Code < 0) {
        printf("Error setting mode\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_MODE32, &_spi__Mode);
    if(ret_Code < 0) {
        printf("Error reading mode\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_BITS_PER_WORD, &_spi__NoOfBits);
    if(ret_Code < 0) {
        printf("Error setting no. bits\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_BITS_PER_WORD, &_spi__NoOfBits);
    if(ret_Code < 0) {
        printf("Error reading no. bits\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_MAX_SPEED_HZ, &_spi__DataRate);
    if(ret_Code < 0) {
        printf("Error setting data rate\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_MAX_SPEED_HZ, &_spi__DataRate);
    if(ret_Code < 0) {
        printf("Error reading data rate\n");
    }

    uint8_t *rx_Buffer = NULL;
    rx_Buffer = malloc(sizeof(uint8_t) * SPI_NO_OF_BYTES_TO_TX);
    if(!rx_Buffer) {
        printf("Error allocating buffer memory");
        goto free_and_close;
    }

    printf("CFG -> MODE: %u, %u, %u\n", _spi__Mode, _spi__NoOfBits, _spi__DataRate);

    if(SPI_HAL_ReceiveData(spi_Handle, rx_Buffer, SPI_NO_OF_BYTES_TO_TX) != 0) {
        printf("Error receiving data");
    }

    free_and_close:
close(spi_Handle);
free(rx_Buffer);

    return 0;
}

static int SPI_HAL_ReceiveData(int spi_fd, uint8_t *rx_buff, size_t data_len) {

    struct spi_ioc_transfer transfer_Obj = {
		.tx_buf = 0,
		.rx_buf = (unsigned long)rx_buff,
		.len = data_len,
		.delay_usecs = 0,
		.speed_hz = _spi__DataRate,
		.bits_per_word = _spi__NoOfBits,
    };

    int ret_Code = 0;
    
    ret_Code = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &transfer_Obj);
    if(ret_Code < 0) {
        printf("Error transitting data");
        return -1;
    }
    printf("Data RX: %u %u\n", ((uint16_t *) rx_buff)[100], ((uint16_t *) rx_buff)[200]);
    printf("Transmission done. \n");
    
    return 0;

}

