#include "PhoneValidator.h"
#include <curl/curl.h>
#include <json/json.h>
#include <sstream>
#include <iostream>
#include <regex>

// Nueva función para validación local básica de números colombianos
bool PhoneValidator::validarNumeroLocalmente(const std::string& phone) {
    // Verifica que el número tenga 10 dígitos y comience con 3 (móviles colombianos)
    std::regex patronColombia("^3[0-9]{9}$");
    return std::regex_match(phone, patronColombia);
}

bool PhoneValidator::validarNumero(const std::string& phone) {
    // Primero hacemos una validación local básica
    if (!validarNumeroLocalmente(phone)) {
        std::cerr << "Error: El número no cumple con el formato de Colombia (10 dígitos, comenzando con 3)" << std::endl;
        return false;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Error: No se pudo inicializar CURL" << std::endl;
        return false;
    }

    std::string apiKey = "b5a079e4b8b84c1e96bf6e27796d2d58";
    std::string country = "CO";
    std::string url = "https://phonevalidation.abstractapi.com/v1/?api_key=" + apiKey + "&phone=" + phone + "&country=" + country;
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error de conexión a la API: " << curl_easy_strerror(res) << std::endl;
        // Si falla la conexión pero pasó la validación local, permitimos el número
        return true;
    }

    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    std::string errs;
    std::istringstream ss(response);

    if (!Json::parseFromStream(builder, ss, &jsonData, &errs)) {
        std::cerr << "Error al analizar la respuesta JSON: " << errs << std::endl;
        // Si no se puede analizar la respuesta pero pasó la validación local, permitimos el número
        return true;
    }

    // Verificamos si hay mensaje de error en la respuesta (límite de API excedido)
    if (jsonData.isMember("error")) {
          "Error de la API: " + jsonData["error"]["message"].asString(); //mostraba el mensaje que envia la API
        // Si el error es por límite de API pero pasó la validación local, permitimos el número
        if (jsonData["error"]["message"].asString().find("limit") != std::string::npos) {
            std::cerr << "Se ha alcanzado el límite de consultas de la API. Usando validación local." << std::endl;
            return true;
        }
        return false;
    }

    // Si todo va bien, validamos con la respuesta de la API
    bool esValido = jsonData["valid"].asBool();

    // Si no es válido según la API, mostramos información detallada
    if (!esValido && jsonData.isMember("format")) {
        std::cerr << "Número rechazado por la API. Detalles:" << std::endl;
        std::cerr << "- Formato: " << jsonData["format"]["local"].asString() << std::endl;
        std::cerr << "- Tipo: " << jsonData["type"].asString() << std::endl;
        if (jsonData.isMember("carrier")) {
            std::cerr << "- Operador: " << jsonData["carrier"].asString() << std::endl;
        }
    }

    return esValido;
}

size_t PhoneValidator::writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}
