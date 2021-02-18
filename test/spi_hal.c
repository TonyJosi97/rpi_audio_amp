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
#define _T_SPI_MODE            (SPI_NO_CS | _T_SPI_CPHA_CPOL)
#define _T_SPI_DATA_RATE       (1000000U)
#define _T_SPI_NO_OF_BITS      (8)
#define _T_SPI_DEVICE_NAME      "/dev/spidev0.0"

/* Slave specific data */
#define DATA_BUFFER_SIZE			2205
#define DATA_BUFFER_SAMPLE_SIZE		(DATA_BUFFER_SIZE * 2)
#define SPI_NO_OF_BYTES_TO_TX		(DATA_BUFFER_SAMPLE_SIZE * 2)

#define TEMP_SIZE_RX                2500

static uint32_t     _spi__Mode          = _T_SPI_MODE;
static uint32_t     _spi__DataRate      = _T_SPI_DATA_RATE;
static uint8_t      _spi__NoOfBits      = _T_SPI_NO_OF_BITS;

static int SPI_HAL_ReceiveData(int spi_fd, uint8_t *rx_buff, size_t data_len);

int main() {

    int spi_Handle;
    spi_Handle = open(_T_SPI_DEVICE_NAME, O_RDWR, 0);
    if(spi_Handle < 0) {
        printf("Error opening device\n");
        return 0;
    }

    int ret_Code = 0;
    uint32_t temp_Val = 0;
    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_MODE, &temp_Val);
    if(ret_Code < 0) {
        printf("Error reading mode\n");
    }
    printf("Data: %u\n", temp_Val);

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_BITS_PER_WORD, &temp_Val);
    if(ret_Code < 0) {
        printf("Error reading no. bits\n");
    }
    printf("Data: %u\n", temp_Val);

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_MAX_SPEED_HZ, &temp_Val);
    if(ret_Code < 0) {
        printf("Error reading data rate\n");
    }
    printf("Data: %u\n", temp_Val);



    /*
    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_MODE, &_spi__Mode);
    if(ret_Code < 0) {
        printf("Error setting mode\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_MODE, &_spi__Mode);
    if(ret_Code < 0) {
        printf("Error reading mode\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_WR_BITS_PER_WORD, &_spi__NoOfBits);
    if(ret_Code < 0) {
        printf("Error setting no. bits\n");
    }

    ret_Code = ioctl(spi_Handle, SPI_IOC_RD_BITS_PER_WORD, &_spi__NoOfBits);
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
    */

    uint8_t *rx_Buffer = NULL;
    rx_Buffer = malloc(sizeof(uint8_t) * TEMP_SIZE_RX);
    if(!rx_Buffer) {
        printf("Error allocating buffer memory");
        goto free_and_close;
    }

    printf("CFG -> MODE: %u, %u, %u\n", _spi__Mode, _spi__NoOfBits, _spi__DataRate);

    while(1) {
        if(SPI_HAL_ReceiveData(spi_Handle, rx_Buffer, TEMP_SIZE_RX) != 0) {
            printf("Error receiving data\n");
        }
        usleep(500 * 1000);
    }

    free_and_close:
close(spi_Handle);
free(rx_Buffer);

    return 0;
}

static int SPI_HAL_ReceiveData(int spi_fd, uint8_t *rx_buff, size_t data_len) {

    /*
    struct spi_ioc_transfer transfer_Obj = {
		.tx_buf = 0,
		.rx_buf = (unsigned long)rx_buff,
		.len = data_len,
		.delay_usecs = 0,
		.speed_hz = _spi__DataRate,
		.bits_per_word = _spi__NoOfBits,
    };

    */
    int ret_Code = 0;
    
    ret_Code = read(spi_fd, rx_buff, data_len);
    if(ret_Code < 0) {
        printf("Error transitting data %d\n", ret_Code);
        return -1;
    }
    printf("Data RX: %u %u\n", ((uint16_t *) rx_buff)[100], ((uint16_t *) rx_buff)[200]);
    printf("Transmission done. \n");
    
    return 0;

}

