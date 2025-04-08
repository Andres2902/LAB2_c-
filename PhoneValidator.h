#ifndef PHONEVALIDATOR_H
#define PHONEVALIDATOR_H

#include <string>
class PhoneValidator {
public:
    static bool validarNumero(const std::string& phone);
    static bool validarNumeroLocalmente(const std::string& phone);
private:
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output);
};

#endif
