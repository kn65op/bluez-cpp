/* 
 * File:   BluezBluetooth.h
 * Author: tomko
 *
 * Created on 26 marzec 2012, 23:21
 */

#ifndef BLUEZBLUETOOTH_H
#define	BLUEZBLUETOOTH_H

#include <list>
#include "Device.h"

class BluezBluetooth
{
public:

  /**
   * Klasa wyjątku w przypadku błędu.
   */
  class BluetoothError
  {
  public:

    BluetoothError(std::string e) : error(e)
    {

    }

    std::string GetError() const
    {
      return error;
    }

  private:
    std::string error;
  };

  /**
   * Klasa wyjątku w przypadku nie znalezienia urządzenia, którego szukamy.
   */
  class NotFound
  {
  };

  BluezBluetooth();
  BluezBluetooth(const BluezBluetooth& orig);
  virtual ~BluezBluetooth();

  /**
   * Funkcja zwracająca listę wykrytych urządzeń. Jeśli wystąpi błąd to rzucany jest wyjątek.
   * @return Lista wykrytych urządzeń.
   */
  std::list<Device> getDevices();
  /**
   * Funkcja zwracająca listę wskaźników do wykrytych urządzeń. Jeśli wystąpi błąd to rzucany jest wyjątek. Jeśli nie jest konieczne używanie wskaźników należy użyć getDevices().
   * Należy zwolnić pamięć używaną przez listę samodzielnie.
   * @return Lista wskaźników do wykrytych urządzeń.
   */
  std::list<Device*> getDevicesPointers();
  /**
   * Funkcja wyszukująca widocznych urządzeń w pobliżu. Jeśli wystąpi błąd to rzucany jest wyjątek.
   */
  void scanDevices() throw (BluetoothError);

  /**
   * Funkcja szukająca urządzeń w zasięgu po adresie MAC. Jeśli nie ma urządzenia o danym adresie to wyrzucany jest wyjątek. Przed wykonaniem wyszukiwania na liście należy wyszukać urządzeń w zasięgu.
   * @param MAC Adres MAC urządzenia, które chcemy znaleźć.
   * @return Znalezione urządzenie.
   */
  Device getDeviceByMAC(std::string MAC) throw (NotFound);

  /**
   * Funkcja szukająca urządzeń w zasięgu po nazwie. Jeśli nie ma urządzenia o danej nazwie to wyrzucany jest wyjątek. Przed wykonaniem wyszukiwania na liście należy wyszukać urządzeń w zasięgu.
   * @param name Nazwa urządzenia, które chcemy znaleźć.
   * @return Znalezione urządzenie.
   */
  Device getDeviceByName(std::string name) throw (NotFound);
  
  /**
   * Funkcja usuwająca z listy znalezionych urządzeń urządzenie o podanym adresie MAC. Jeśli podanego urządzenia nie ma na liście to nic się nie dzieje.
   * @param MAC Adres MAC urządzenia do usunięcia.
   * @return true jeśli usunięto urządzenie, false w przeciwnym wypadku
   */
  bool deleteByMAC(std::string MAC);
  /**
   * Funkcja usuwają z listy znalezionych urządzeń urządzenie o podanej nazwie. Jeśli podanego urządzenia nie ma na liście to nic się nie dzieje.
   * @param name Nazwa urządzenia do usunięcia.
   * @return true jeśli usunięto urządzenie, false w przeciwnym wypadku
   */
  bool deleteByName(std::string name);


private:
  std::list<Device> devices;
  void scan() throw (BluetoothError);
  
  /**
   * Szuakanie na liście urządzenia o podanym MAC.
   * @param MAC MAC szukanego urządzenia.
   * @return Iterator do listy jeśli znaledziono lub iterator end w razie braku urządzenia na liście.
   */
  std::list<Device>::iterator findByMAC(std::string MAC);
  /**
   * Szuakanie na liście urządzenia o podanej nazwie.
   * @param name Nazwa szukanego urządzenia.
   * @return Iterator do listy jeśli znaledziono lub iterator end w razie braku urządzenia na liście.
   */
  std::list<Device>::iterator findByName(std::string name);
};

#endif	/* BLUEZBLUETOOTH_H */

